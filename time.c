#include <assert.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "server.h"

/* A template for the HTML page this module generates.  */

static char* page_template = 
	"<html>\n"
	" <head>\n"
	"  <title>System time</title>\n"
	"  <meta http-equiv=\"refresh\" content=\"15\">\n"
	"  <link rel=\"stylesheet\" href=\"http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css\">\n"
	"  <style>\n"
	"   pre {\n"
	"    white-space: pre-wrap;\n"
	"    word-wrap: break-word;\n"
	"   }\n"
	"   body {\n"
    "    color: #cccccc;\n"
    "    background-color: #003050;\n"
	"   }\n"
	"  </style>\n"
	" </head>\n"
	" <body>\n"
	"  <nav class=\"navbar navbar-default\">\n"
	"   <div class=\"container-fluid\">\n"
    "    <div class=\"navbar-header\">\n"
    "     <a class=\"navbar-brand\" href=\"#\">WebMonitor</a>\n"
    "      </div>\n"
    "       <ul class=\"nav navbar-nav\">\n"
    "        <li><a href=\"#\">Home</a></li>\n"
    "        <li><a href=\"/cpuinfo\">cpuinfo</a></li>\n"
    "        <li><a href=\"/diskfree\">diskfree</a></li>\n"
    "        <li><a href=\"/issue\">issue</a></li>\n"
    "        <li class=\"active\"><a href=\"/time\">time</a></li>\n"
    "        <li><a href=\"/processes\">processes</a></li>\n"
    "       </ul>\n"
	"      </div>\n"
	"     </nav>\n"
	"   <pre>\n"
	"  <p class=\"text-center\">The current time is %s.</p>\n"
	"   </pre>\n"
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
	/* Generate the HTML output.  */
	fprintf (fp, page_template, time_string);
	/* All done; flush the stream. */
	fflush (fp);
}
