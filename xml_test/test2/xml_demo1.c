/*************************************************************************
    > File Name: xml_demo1.c
    > Author: yanghang
    > Mail: 2459846416@qq.com 
    > Created Time: Sun 02 Dec 2018 04:10:49 PM CST
 ************************************************************************/

#include<stdio.h>
#include"mxml.h"

int main(void)
{
	FILE *fp = fopen("01new_xml.xml", "w");
	
	//step1 <?xml version=”1.0” encoding = “utf-8”?> 
	mxml_node_t *xml = mxmlNewXML("1.0");

	//step2 向一个节点新增一个节点
	mxml_node_t *note = mxmlNewElement(xml, "note");

	mxml_node_t *to = mxmlNewElement(note, "to");
	mxmlNewText(to, 0, "LuoYuLong");
	mxmlElementSetAttr(to, "time", "0214");

	mxml_node_t *from = mxmlNewElement(note, "from");
	mxmlNewText(from, 0, "Jani");

	mxml_node_t *heading = mxmlNewElement(note, "heading");
	mxmlNewText(heading, 0, "Reminder");

	mxml_node_t *body = mxmlNewElement(note, "body");
    mxmlNewText(body, 0, "Don't forget me this weekend!");

	mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);

	fclose(fp);

	return 0;
}


