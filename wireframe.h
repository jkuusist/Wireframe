#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <SDL2/SDL.h>
#include <vector>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

typedef struct	s_point
{
	float x;
	float y;
	float z;
}				t_point;

typedef struct	s_int_point
{
	int x;
	int y;
	int z;
}				t_int_point;

typedef struct 	s_camera
{
	float	x_rotation;
	float	y_rotation;
	float	z_rotation;
	int	zoom;
}				t_camera;

class matrix44
{
public:

	float x[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

	matrix44() {}

	matrix44(float a, float b, float c, float d, float e, float f, float g, float h,
			float i, float j, float k, float l, float m, float n, float o, float p )
	{
		x[0][0] = a;
        x[0][1] = b;
        x[0][2] = c;
        x[0][3] = d;
        x[1][0] = e;
        x[1][1] = f;
        x[1][2] = g;
        x[1][3] = h;
        x[2][0] = i;
        x[2][1] = j;
        x[2][2] = k;
        x[2][3] = l;
        x[3][0] = m;
        x[3][1] = n;
        x[3][2] = o;
        x[3][3] = p;
	}

	const float	*operator [] (unsigned int i) const {return x[i];}
	float		*operator [] (unsigned int i) {return x[i];}
	matrix44 	operator * (const matrix44& v) const
	{
		matrix44 temp;
		multiply(*this, v, temp);

		return (temp);
	}

	static void	multiply(const matrix44 &a, const matrix44& b, matrix44 &c)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				c[i][j] = (a[i][0] * b[0][j]) + (a[i][1] * b[1][j]) + (a[i][2] * b[2][j]) +
						(a[i][3] * b[3][j]);
			}
		}
	}

	const matrix44& invert()
	{
		*this = inverse();
		return *this;
	}

	matrix44 inverse() const
	{
		int i, j, k;
		matrix44 res;
		matrix44 t (*this);

		for (i = 0; i < 3; i++)
		{
			int pivot = i;
			float pivot_size = t[i][i];

			if (pivot_size < 0)
				pivot_size = -pivot_size;

			for (j = i + 1; j < 4; j++)
			{
				float temp = t[j][i];

				if (temp < 0)
					temp = -temp;

				if (temp > pivot_size)
				{
					pivot = j;
					pivot_size = temp;
				}
			}

			if (pivot_size == 0)
				return matrix44();

			if (pivot != i)
			{
				for (j = 0; j < 4; j++)
				{
					float temp = t[i][j];

					t[i][j] = t[pivot][j];
					t[pivot][j] = temp;

					temp = res[i][j];
					res[i][j] = res[pivot][j];
					res[pivot][j] = temp;
				}
			}

			for (j = i + 1; j < 4; j++)
			{
				float f = t[j][i] / t[i][i];

				for (k = 0; k < 4; k++)
				{
					t[j][k] -= f * t[i][k];
					res[j][k] -= f * res[i][k];
				}
			}
		}

		for (i = 3; i >= 0; i--)
		{
			float f = t[i][i];

			if (f == 0)
				return matrix44();

			for (j = 0; j < 4; j++)
			{
				t[i][j] /= f;
				res[i][j] /= f;
			}

			for (j = 0; j < i; j++)
			{
				f = t[j][i];
			
				for (k = 0; k < 4; k++)
				{
					t[j][k] -= f * t[i][k];
					res[j][k] -= f * res[i][k]; 
				}
			}
		}

		return (res);
	}
};

void	draw_line(t_int_point start, t_int_point end, SDL_Renderer *renderer);
std::vector<std::vector<t_point>>	handle_input(int argc, char *args[]);
std::vector<std::vector<t_int_point>> convert_coordinates(std::vector<std::vector<t_point>> points, t_camera *camera);
void multiply_point_matrix(t_point *point, matrix44 matrix);
void rotate_point(t_int_point *point, t_camera *camera);
void mouse_rotation(t_camera *camera);

#endif
