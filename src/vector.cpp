#include "vector.h"

Vector vec_v(float x, float y)
{
	Vector myVec;
	myVec.x = x;
	myVec.y = y;
	return myVec;
}

Vector print_v(Vector vec)
{
	printf("(%f, %f)\n", vec.x, vec.y);
	return vec;
}

Vector invert_v(Vector vec)
{
	return vec_v(-vec.x, -vec.y);
}

float get_norm_v(Vector vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y);
}

float dist_v(Vector vec1, Vector vec2)
{
	Vector diffVec = vec1 - vec2;
	return get_norm_v(diffVec);
}

Vector abs_v(Vector vec)
{
	return vec_v(abs(vec.x), abs(vec.y));
}

float dot_v(Vector veca, Vector vecb)
{
	return veca.x*vecb.x + veca.y*vecb.y;
}

float det_v(Vector veca, Vector vecb)
{
	return veca.x * vecb.y - veca.y * vecb.x;
}

Vector normalize_v(Vector vec)
{
	return vec / get_norm_v(vec);
}

Vector max_v(Vector vec, float scalMax)
{
	return vec_v(fmax(vec.x, scalMax), fmax(vec.y, scalMax));
}

Vector min_v(Vector vec, float scalMin)
{
	return vec_v(fmin(vec.x, scalMin), fmin(vec.y, scalMin));
}

float get_angle_v(Vector vec)
{
	return atan2(vec.y,vec.x);
}

float get_angle_two_vec_v(Vector veca, Vector vecb)
{
	float angle = acos(  dot_v(veca, vecb) / (get_norm_v(veca) * get_norm_v(vecb))  );
	return angle;
}

float angle_btw_pos_v(Vector posa, Vector posb)
{
	Vector vec = posb - posa;
	Vector left = vec_v(-1.f, 0.f);
	float angle = get_angle_two_vec_v(vec, left);
	angle = 2*PI - angle;
	if (posa.y > posb.y)
	{
		angle = 2*PI - angle;
	}
	return angle;
}

Vector vec_from_angle_v(float angle)
{
	Vector vec;
	vec.x = cos(angle);
	vec.y = sin(angle);
	return vec;
}

Vector random_vec_v(int minX, int maxX, int minY, int maxY)
{
	Vector vec;
	vec.x = (float)((rand() % (maxX + abs(minX))) - minX);
	vec.y = (float)((rand() % (maxY + abs(minY))) - minY);
	return vec;
}

sf::Vector2f vec_to_sfvec2_v(Vector vec)
{
	return sf::Vector2f(vec.x, vec.y);
}

Vector sfvec2_to_vec_v(sf::Vector2f vec)
{
	return vec_v(vec.x, vec.y);
}

Vector mult_comp_c(Vector a, Vector b)
{
	return vec_v(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
}

Vector conjugate_c(Vector z)
{
	return vec_v(z.x, -z.y);
}
Vector divide_comp_c(Vector a, Vector b)
{
	return vec_v(((a.x*b.x+a.y*b.y)/(b.x*b.x+b.y*b.y)),((a.y*b.x-a.x*b.y)/(b.x*b.x+b.y*b.y)));
}
Vector power_comp_c(Vector a, int p)
{
  	Vector result = a;
  	for (int i = 0; i < p-1; ++i)
  	{
    	result = mult_comp_c(result,a);
	}
	return result;
}


Vector operator+(const Vector& a, const Vector& b)
{
	return vec_v(a.x + b.x, a.y + b.y);
}

Vector operator-(const Vector& a, const Vector& b)
{
	return a + invert_v(b);
}

Vector operator+(const Vector& a, float scalar)
{
	return vec_v(a.x + scalar, a.y + scalar);
}

Vector operator-(const Vector& a, float scalar)
{
	return a + (-scalar);
}

Vector operator/(const Vector& a, float scalar)
{
	if(scalar == 0)
	{
		return a;
	}
	return vec_v(a.x / scalar, a.y / scalar);
}

Vector operator/(const Vector& a, const Vector& b)
{
	Vector result;
	if (a.x == 0)
	{
		result.x = b.x;
	}
	else
	{
		result.x = b.x / a.x;
	}
	if (a.y == 0)
	{
		result.y = b.y;
	}
	else
	{
		result.y = b.y / a.y;
	}
	return result;
}

bool operator==(const Vector& a, const Vector& b)
{
	return a.x == b.x && a.y == b.y;
}

Vector operator*(const Vector& a, float scalar)
{
	return vec_v(a.x * scalar, a.y * scalar);
}
