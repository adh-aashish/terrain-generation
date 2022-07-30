#include "../include/cube.h"
#include "../include/glMath.h"
#include "../include/constants.h"

Cube::Cube(sf::RenderWindow& w): window(&w),model(glMath::mat4f(1.0f)),view(1.0f),proj(1.0f) {

	local.tris = {
		// SOUTH
		{ glMath::vec3f(-0.5f, -0.5f, 0.5f),    glMath::vec3f(-0.5f, 0.5f, 0.5f),    glMath::vec3f(0.5f, 0.5f, 0.5f) },
		{ glMath::vec3f(-0.5f, -0.5f, 0.5f),    glMath::vec3f(0.5f, 0.5f, 0.5f),     glMath::vec3f(0.5f, -0.5f, 0.5f) },

		// EAST                                                      
		{ glMath::vec3f(0.5f, -0.5f, 0.5f),     glMath::vec3f(0.5f, 0.5f, 0.5f),     glMath::vec3f(0.5f, 0.5f, -0.5f) },
		{ glMath::vec3f(0.5f, -0.5f, 0.5f),     glMath::vec3f(0.5f, 0.5f, -0.5f),    glMath::vec3f(0.5f, -0.5f, -0.5f) },

		// NORTH                                                     
		{ glMath::vec3f(-0.5f, -0.5f, -0.5f),   glMath::vec3f(-0.5f, 0.5f, -0.5f),    glMath::vec3f(0.5f, 0.5f, -0.5f) },
		{ glMath::vec3f(-0.5f, -0.5f, -0.5f),   glMath::vec3f(-0.5f, -0.5f, -0.5f),   glMath::vec3f(0.5f, -0.5f, -0.5f) },

		// WEST                                                      
		{ glMath::vec3f(-0.5f, -0.5f, 0.5f),    glMath::vec3f(-0.5f, 0.5f, 0.5f),    glMath::vec3f(-0.5f, 0.5f, -0.5f) },
		{ glMath::vec3f(-0.5f, -0.5f, 0.5f),    glMath::vec3f(-0.5f, 0.5f, -0.5f),   glMath::vec3f(-0.5f, -0.5f, -0.5f) },

		// TOP                                                       
		{ glMath::vec3f(-0.5f, 0.5f, 0.5f),     glMath::vec3f(-0.5f, 0.5f, -0.5f),   glMath::vec3f(0.5f, 0.5f, -0.5f) },
		{ glMath::vec3f(-0.5f, 0.5f, 0.5f),     glMath::vec3f(0.5f, 0.5f, -0.5f),    glMath::vec3f(0.5f, 0.5f, 0.5f) },

		// BOTTOM                                                    
		{ glMath::vec3f(-0.5f, -0.5f, 0.5f),    glMath::vec3f(-0.5f, -0.5f, -0.5f),   glMath::vec3f(0.5f, -0.5f, -0.5f) },
		{ glMath::vec3f(-0.5f, -0.5f, 0.5f),    glMath::vec3f(0.5f, -0.5f, -0.5f),    glMath::vec3f(0.5f, -0.5f, 0.5f) }

	};

	// color = sf::Color(255,255,255);
	first = true;
}

void Cube::drawTriangle(glMath::vec3f p1, glMath::vec3f p2, glMath::vec3f p3, sf::Color color)
{
	// change to window coordinate first
	// p1.x = (p1.x+1) * 540;
	// p1.y = (p1.y-1) * -360;
	// p2.x = (p2.x+1) * 540;
	// p2.y = (p2.y-1) * -360;
	// p3.x = (p3.x+1) * 540;
	// p3.y = (p3.y-1) * -360;

	p1.x = (int)( ((p1.x+1) * 540) + 0.5 );
	p1.y = (int)( ((p1.y-1) * -360) + 0.5);
	p2.x = (int)( ((p2.x+1) * 540) + 0.5);
	p2.y = (int)( ((p2.y-1) * -360) + 0.5);
	p3.x = (int)( ((p3.x+1) * 540) + 0.5);
	p3.y = (int)( ((p3.y-1) * -360) + 0.5);

	if (first)
	{
		BLA(p1.x, p1.y, p2.x, p2.y, color);
		BLA(p2.x, p2.y, p3.x, p3.y, color);
	}
	else
	{
		BLA(p2.x, p2.y, p3.x, p3.y, color);
		BLA(p3.x, p3.y, p1.x, p1.y, color);
	}
	first = (first)? false:true;
}

void Cube::BLA(int x0, int y0, int xl, int yl, sf::Color color)
{
	int delx = std::fabs(xl - x0);
	int dely = std::fabs(yl - y0);
	int a = 0, b = 0;
	int p = 0;
	a = ((xl - x0) > 0) ? 1 : -1;
	b = ((yl - y0) > 0) ? 1 : -1;
	if (delx > dely)
	{
		p = 2 * dely - delx;
		for (int i = 0; i <= delx; i++)
		{
			putpixel(x0, y0, color);
			x0 += a;
			if (p <= 0)
				p += 2 * dely;
			else
			{
				p += 2 * dely - 2 * delx;
				y0 += b;
			}
		}
	}
	else
	{
		p = 2 * delx - dely;
		for (int i = 0; i <= dely; i++)
		{
			putpixel(x0, y0, color);
			y0 += b;
			if (p <= 0)
				p += 2 * delx;
			else
			{
				p += 2 * delx - 2 * dely;
				x0 += a;
			}
		}
	}
}

void Cube::putpixel(float x, float y, sf::Color color)
{
	sf::Vertex vertex(sf::Vector2f(x, y), color);
	window->draw(&vertex, 1, sf::Points);
}

void Cube::render()
{
	for (auto &i : meshCube.tris)
	{
		fillTriangle(sf::Vector2f(i.p[0].x, i.p[0].y),
					sf::Vector2f(i.p[1].x, i.p[1].y), sf::Vector2f(i.p[2].x, i.p[2].y), sf::Color(255,255,255));
		// drawTriangle(i.p[0], i.p[1], i.p[2], sf::Color(255,0,0));
	}
}
  
void Cube::translate(glMath::vec3f p)
{
	p.x = (float)(2*p.x)/constants::SCREEN_WIDTH;
	p.y = (float)(2 * p.y)/constants::SCREEN_HEIGHT;
	// p.z = (p.y)/720.f;
	// p1.x = (p1.x+1) * 540;
	// p1.y = (p1.y-1) * -360;
	// p.normalize();

	model = glMath::translate<float>(model, p);
}

void Cube::rotate(glMath::vec3f p, float angle)
{
	model = glMath::rotate<float>(model, glMath::degToRadians(angle) ,p);
}

void Cube::scale(glMath::vec3f p)
{
	model = glMath::scale<float>(model, p);
}

void Cube::perspective(float fov,float sw,float sh,float nearZ,float farZ){
	proj = glMath::perspective<float>(fov,sw,sh,nearZ,farZ);
}

void Cube::lookAt(glMath::vec3f  from, glMath::vec3f  to, glMath::vec3f  temp){
	view = glMath::lookAt<float>(from,to,temp);
}

// fills the meshcube upto to be rendered part i.e. upto projection done
void Cube::updateVertices()
{
	meshCube.tris.clear();
	for (auto i : local.tris) {
		glMath::trianglef t;
		int count = 0;
		for (auto j : i.p)
		{
			glMath::vec4f v (j.x, j.y, j.z,1);
			v =  (proj*(view * model)) * v;
			if(v.w!=1 and v.w!=0){
				v.x /= v.w;
				v.y /= v.w;
				v.z /= v.w;
				v.w = 1;
			}
			t.p[count++] = glMath::vec3f(v.x, v.y, v.z);
		}
		meshCube.tris.push_back(t);
	}
}

void Cube::toWindowCoord()
{
	for (auto &i : meshCube.tris) {
		for (auto &j : i.p)
		{
			glMath::vec3f v(j.x, j.y, j.z);
			j = glMath::vec3f((v.x + 1)*540, (v.y-1)*(-360), v.z);
		}
	}
	
}

void Cube::fillBottomFlatTriangle(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3, sf::Color color)
{
  float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
  float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

  float curx1 = v1.x;
  float curx2 = v1.x;

  for (int scanlineY = v1.y; scanlineY <= v2.y; scanlineY++)
  {
    // BLA((int)curx1, scanlineY, (int)curx2, scanlineY, 1);
	scanLine((int)curx1, scanlineY, (int)curx2, scanlineY, color);
    curx1 += invslope1;
    curx2 += invslope2;
  }
}

void Cube::fillTopFlatTriangle(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3, sf::Color color)
{
  float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
  float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

  float curx1 = v3.x;
  float curx2 = v3.x;

  for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--)
  {
    // BLA((int)curx1, scanlineY, (int)curx2, scanlineY, 1);
	scanLine((int)curx1, scanlineY, (int)curx2, scanlineY, color);
    curx1 -= invslope1;
    curx2 -= invslope2;
  }
}

void Cube::scanLine(int x0, int y0, int x1, int y1, sf::Color color)
{
	int delx = std::fabs(x1 - x0);
    int a = 0;
	a = ((x1 - x0) > 0) ? 1 : -1;

	for(int i=0; i<= delx; i++)
	{
		putpixel(x0, y0, color);
		x0 += a;
	}
}

void Cube::fillTriangle(sf::Vector2f vt1, sf::Vector2f vt2, sf::Vector2f vt3, sf::Color color)
{

	// vt1.x = (vt1.x+1) * 540;
	// vt1.y = (vt1.y-1) * -360;
	// vt2.x = (vt2.x+1) * 540;
	// vt2.y = (vt2.y-1) * -360;
	// vt3.x = (vt3.x+1) * 540;
	// vt3.y = (vt3.y-1) * -360;

	vt1.x = (int)( ((vt1.x+1) * 540) + 0.5 );
	vt1.y = (int)( ((vt1.y-1) * -360) + 0.5);
	vt2.x = (int)( ((vt2.x+1) * 540) + 0.5);
	vt2.y = (int)( ((vt2.y-1) * -360) + 0.5);
	vt3.x = (int)( ((vt3.x+1) * 540) + 0.5);
	vt3.y = (int)( ((vt3.y-1) * -360) + 0.5);

	std::vector<sf::Vector2f> v;
	v.push_back(vt1);
	v.push_back(vt2);
	v.push_back(vt3);

	/* at first sort the three vertices by y-coordinate ascending so v1 is the topmost vertice */
	//   sortVerticesAscendingByY();

	for (unsigned int i = 0; i < v.size(); i++)
	{
		for (auto itj = v.begin(); itj != v.end()-1; itj = std::next(itj))
		{
			if ((*itj).y > (*std::next(itj)).y)
			{
				std::swap(*itj, *std::next(itj)); 
			}
		}
	}

	vt1 = v.at(0);
	vt2 = v.at(1);
	vt3 = v.at(2);
	/* here we know that v1.y <= v2.y <= v3.y */
	/* check for trivial case of bottom-flat triangle */
	if (vt2.y == vt3.y)
	{
		fillBottomFlatTriangle(vt1, vt2, vt3, color);
	}
	/* check for trivial case of top-flat triangle */
	else if (vt1.y == vt2.y)
	{
		fillTopFlatTriangle( vt1, vt2, vt3, color);
	}
	else
	{
		/* general case - split the triangle in a topflat and bottom-flat one */
		sf::Vector2f v4 = sf::Vector2f(
		(int)(vt1.x + ((float)(vt2.y - vt1.y) / (float)(vt3.y - vt1.y)) * (vt3.x - vt1.x)), vt2.y);
		fillBottomFlatTriangle( vt1, vt2, v4, color);
		fillTopFlatTriangle( vt2, v4, vt3, color);
	}

}
