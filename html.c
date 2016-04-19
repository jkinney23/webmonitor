#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "html.h"

/* The html for the start of all the pages  */
static char* p_start = 
	"<!DOCTYPE html>\n"
	"<html>\n"
	" <head>\n"
	"  <title>%s</title>\n"
	"  <link rel=\"stylesheet\" href=\"http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css\">\n"
	"  <style>\n"
	"   body {\n"
	"    color: #cccccc;\n"
	"    background-color: #003050;\n"
	"   }\n"
	"   .container {\n"
	"    margin-left: auto;\n"
	"    margin-right: auto;\n"
	"    text-align: right;\n"
	"   }\n"
	"   pre {\n"
	"    white-space: pre-wrap;\n"
	"    word-wrap: break-word;\n"
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
	"        <li%s><a href=\"#\">Home</a></li>\n"
	"        <li%s><a href=\"/cpuinfo\">cpuinfo</a></li>\n"
	"        <li%s><a href=\"/diskfree\">diskfree</a></li>\n"
	"        <li%s><a href=\"/issue\">issue</a></li>\n"
	"        <li%s><a href=\"/processes\">processes</a></li>\n"
	"        <li%s><a href=\"/time\">time</a></li>\n"
	"       </ul>\n"
	"      </div>\n"
	"     </nav>\n"
	"%s";

char *generate_head(char* title, int active_index, int pre)
{
	char* argv[7];
	char* head = malloc(strlen(p_start) + strlen(title) + 17 + 11 + 1);
	int i;
	
	/* fill in args  */
	for(i = 0; i < 7; i++)
	{
		if(i == active_index)
		{
			argv[i] = " class=\"active\"";
		}
		else
		{
			argv[i] = "";
		}
	}
	if (pre)
	{
		argv[6] = "   <pre>\n";
	}

	/* generate the page start  */
	sprintf(head, p_start, title, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
	return head;
}

