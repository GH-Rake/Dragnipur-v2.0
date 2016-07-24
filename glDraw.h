#pragma once

GLfloat viewport[4] = { 0 };
GLfloat depthrange[2] = { 0 };
#define WINDOWWIDTH viewport[2]
#define WINDOWHEIGHT viewport[3]

//draw rectangle outline
void drawRectangle(MyRect r, float lineWidth)
{
	vec2 vertices[4] = { r.tl, r.tr, r.br, r.bl };
	initGLDraw();
	glLineWidth(lineWidth);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void drawFilledRect(MyRect r)
{
	vec2 vertices[6] = { r.tr, r.br, r.tl,   // First triangle
						 r.tl, r.br, r.bl }; // Second triangle
	initGLDraw();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 3, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

//ESP text
void renderText(std::string textString, void* font, float xpos, float ypos)
{
	glRasterPos2f(xpos, ypos);
	for (std::string::iterator j = textString.begin(); j != textString.end(); ++j)
	{
		char c = *j;
		glutBitmapCharacter(font, c);
	}
}

void drawOutline(MyRect box)
{
	//maybe subtract 2 from left and leave right alone
	box.tl.x -= 1.0f;
	box.tl.y -= 1.0f;

	//box.tr.x += 1.0f;
	box.tr.x += 0.5f;

	box.tr.y -= 1.0f;

	//box.br.x += 1.0f;
	box.br.x += 0.5f;

	box.br.y += 1.0f;
	box.bl.x -= 1.0f;
	box.bl.y += 1.0f;
	drawRectangle(box, 2.0f);
}

void drawCrosshair()
{
	initGLDraw();
	glColor3ub(240, 240, 240);//white
	glLineWidth(2.0);

	int crossHair[8] = { WINDOWWIDTH / 2 - 7, WINDOWHEIGHT / 2,// horizontal line
		WINDOWWIDTH / 2 + 7, WINDOWHEIGHT / 2,
		WINDOWWIDTH / 2, WINDOWHEIGHT / 2 + 7, //vertical line
		WINDOWWIDTH / 2, WINDOWHEIGHT / 2 - 7 };

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_INT, 0, crossHair);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}