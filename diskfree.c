#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "server.h"
#include "html.h"

/* HTML source for the start of the page we generate.  */
/*
static char* page_start = 
	"<html>\n"
	" <head>\n"
	"  <title>Disk Usage and Free Space</title>\n"
	"  <link rel=\"stylesheet\" href=\"http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css\">\n"
	"  <style>\n"
	//~ "   pre {\n"
	//~ "    white-space: pre-wrap;\n"
	//~ "    word-wrap: break-word;\n"
	//~ "   }\n"
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
    "        <li class=\"active\"><a href=\"/diskfree\">diskfree</a></li>\n"
    "        <li><a href=\"/issue\">issue</a></li>\n"
    "        <li><a href=\"/time\">time</a></li>\n"
    "        <li><a href=\"/processes\">processes</a></li>\n"
    "       </ul>\n"
	"      </div>\n"
	"     </nav>\n"
	"   <pre>\n";
*/	
/* HTML source for the end of the page we generate.  */

static char* page_end = 
	"  </pre>\n"
	" </body>\n"
	"</html>\n";
	
void module_generate (int fd)
{
	pid_t child_pid;
	int rval;
	
	/* Write the start of the page.  */
	char* page_start = generate_head("Disk Usage and Free Space", 2, 1);
	write (fd, page_start, strlen (page_start));
	/* Fork a child process.  */
	child_pid = fork ();
	if (child_pid == 0) {
		/* This is the child process.  */
		/* Set up an argument list for the invocation of df.  */
		char* argv[] = { "/bin/df", "-h", NULL }; // <----- adapt here?
		
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
