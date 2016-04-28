#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "server.h"
#include "html.h"

/* HTML source for the end of the page we generate.  */
static char* page_end = 
	"  </pre>\n"
	"<div class=\"col-md-2 col-md-offset-3\">"
	"<a href=\"/time\" class=\"btn btn-default btn-block\" role=\"button\">Previous</a>"
	"</div>"
	"<div class=\"col-md-2\">"
	"<a href=\"/\" class=\"btn btn-default btn-block\" role=\"button\">Home</a>"
	"</div>"
	"<div class=\"col-md-2\">"
	"<a href=\"#\" class=\"btn btn-default btn-block disabled\" role=\"button\">Next</a>"
	"</div>"
	" </body>\n"
	"</html>\n";
	
void module_generate (int fd)
{
	pid_t child_pid;
	int rval;
	
	/* Generate and write the start of the page.  */
	char* page_start = generate_head("Top Info", 6, 1);
	write (fd, page_start, strlen (page_start));
	
	/* Fork a child process.  */
	child_pid = fork ();
	if (child_pid == 0) {
		/* This is the child process.  */
		/* Set up an argument list for the invocation of df.  */
		char* argv[] = { "/usr/bin/top", "-bn1", NULL }; // <----- adapt here?
		
		/* Duplicate stdout and stderr to send data to the client socket.  */
		rval = dup2 (fd, STDOUT_FILENO);
		if (rval == -1)
			system_error ("dup2");
		rval = dup2 (fd, STDERR_FILENO);
		if (rval == -1)
			system_error ("dup2");
		/* Run df to show the free space on mounted files systems.  */
		execv (argv[0], argv);
		/* A call to execv does not return unless an error occurred.  */
		system_error ("execv");
	}
	else if (child_pid > 0) {
		/* This is the parent process.  Wait for the child process to
		 * finish.  */
		rval = waitpid (child_pid, NULL, 0);
		if (rval == -1)
			system_error ("waitpid");
	}
	else
		/* The call to fork failed.  */
		system_error ("fork");

	/* Write the end of the page.  */
	write (fd, page_end, strlen (page_end));
}
