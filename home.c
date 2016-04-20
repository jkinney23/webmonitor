#include <fcntl.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "server.h"
#include "html.h"
	
/* HTML source for the end of the page we generate.  */
static char* page_end = 
	" </body>\n"
	"</html>\n";
	
/* HTML source for the page indicating there was a problem opening
 * /etc/issue.  */
static char* error_page = 
	"<html>\n"
	" <body>\n"
	"  <p>Error: could not open /etc/issue/</p>\n"
	" </body>\n"
	"</html>\n";

/* HTML source indicating an error.  */
static char* error_message = "Error reading /etc/issue.";

void module_generate (int fd)
{
	int input_fd;
	struct stat file_info;
	int rval;
	
	/* Open /etc/issue.  */
	input_fd = open ("./home.html", O_RDONLY);
	if (input_fd == -1)
		system_error ("open");
	/* Obtain file information about it.  */
	rval = fstat (input_fd, &file_info);
	
	if (rval == -1)
		/* Either we couldn't open the file or we couldn't read from it.  */
		write (fd, error_page, strlen (error_page));
	else {
		int rval;
		off_t offset = 0;
		
		/* Generate and write the start of the page.  */
		char* page_start = generate_head("issue", 0, 0);
		write (fd, page_start, strlen (page_start));
		
		/* Copy from /etc/issue to the client socket.  */
		rval = sendfile (fd, input_fd, &offset, file_info.st_size - 8);
		if (rval == -1)
			/* Something went wrong sending the contents of /etc/issue.
			 * write an error message.  */
			write (fd, error_message, strlen (error_message));
		/* End the page.  */
		write (fd, page_end, strlen (page_end));
	}
	
	close (input_fd);
}
