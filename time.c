#include <assert.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"
#include "html.h"

/* A template for the HTML this module generates.  */
static char* time_template = 
	"  <meta http-equiv=\"refresh\" content=\"15\">\n"
	"  <p class=\"text-center\">The current time is: <strong>%s</strong></p>\n"
	"   </pre>\n"
	"<div class=\"col-md-2 col-md-offset-3\">"
	"<a href=\"/processes\" class=\"btn btn-default btn-block\" role=\"button\">Previous</a>"
	"</div>"
	"<div class=\"col-md-2\">"
	"<a href=\"/\" class=\"btn btn-default btn-block\" role=\"button\">Home</a>"
	"</div>"
	"<div class=\"col-md-2\">"
	"<a href=\"/top\" class=\"btn btn-default btn-block\" role=\"button\">Next</a>"
	"</div>"
	" </body>\n"
	"</html>\n";
	
void module_generate (int fd)
{
	struct timeval tv;
	struct tm* ptm;
	char time_string[40];
	FILE* fp;
	
	/* Obtain the time of day, and convert it to a tm struct.  */
	gettimeofday (&tv, NULL);
	ptm = localtime (&tv.tv_sec);
	
	/* Format the date and time, down to a single second.  */
	strftime (time_string, sizeof(time_string), "%H:%M:%S", ptm);
	
	/* Create a stream corresponding to the client socket file
	 * descriptor.  */
	fp = fdopen (fd, "w");
	assert (fp != NULL);
	
	/* generate the page_template  */
	char* page_head = generate_head("System Time", 5, 1);
	char* page_template = malloc(strlen(page_head) + strlen(time_template) + 1);
	page_template = strcat(page_head, time_template);
	
	/* Generate the HTML output.  */
	fprintf (fp, page_template, time_string);
	//~ free(page_head);
	//~ free(page_template);
	
	/* All done; flush the stream. */
	fflush (fp);
}
