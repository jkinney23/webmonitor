#include <stdio.h>
#include <stdlib.h>

static char* p_start = 
	"<!DOCTYPE html>\n"
	"<html>\n"
	" <head>\n"
	"  <title>%s</title>\n"
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
    "     <a class=\"navbar-brand\" href=\"#\">WebSiteName</a>\n"
    "      </div>\n"
    "       <ul class=\"nav navbar-nav\">\n"
    "        <li class=\"active\"><a href=\"#\">Home</a></li>\n"
    "        <li><a href=\"/cpuinfo\">cpuinfo</a></li>\n"
    "        <li><a href=\"/issue\">issue</a></li>\n"
    "        <li><a href=\"/time\">time</a></li>\n"
    "        <li><a href=\"/processes\">processes</a></li>\n"
    "       </ul>\n"
	"      </div>\n"
	"     </nav>\n"
	"   <pre>\n";
		
char *generate_head(char* title)
{
	char* head = malloc(strlen(p_start) + strlen(title));
	sprintf(head, p_start, title);
	printf("%s", head);
	return head;
}
