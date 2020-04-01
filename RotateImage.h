// RotateImage.h
// Contains the Rotate() function which deals with
// rotating images and displaying rotated images.

using namespace System; // Math operations
using namespace System::Drawing; // Image, Point, Graphics operations
using namespace System::Windows::Forms; // Control

// Overload 1: Rotates the given image by the specified angle about its central point and
// returns three of the four points that surround the rotated image.
// If pt4 is set to true, it returns the fourth point as well.

System::Drawing::Point Rotate(Image *img, double angle_in, float cx, float cy, bool pt4)[]
{
	double r, angle_base, size_x, size_y, xn1, yn1;
	size_x = img->get_Width();
	size_y = img->get_Height();
	angle_in *= Math::PI / 180;
	r = Math::Sqrt(Math::Pow(size_x / 2, 2) + Math::Pow(size_y / 2, 2));
	angle_base = Math::Atan(size_y/size_x);
	xn1 = cx - (r * Math::Cos(angle_in + angle_base));
	yn1 = cy - (r * Math::Sin(angle_in + angle_base));
	if (pt4 == true)
	{
		Point cps[] =
		{
			Point(xn1, yn1),
			Point(xn1 + (size_x * Math::Cos(angle_in)), yn1 + (size_x * Math::Sin(angle_in))),
			Point(xn1 - (size_y * Math::Sin(angle_in)), yn1 + (size_y * Math::Cos(angle_in))),
			Point(cx + (r * Math::Cos(angle_in + angle_base)), cy + (r * Math::Sin(angle_in + angle_base)))
		};
		return cps;
	}
	else
	{
		Point cps[] =
		{
			Point(xn1, yn1),
			Point(xn1 + (size_x * Math::Cos(angle_in)), yn1 + (size_x * Math::Sin(angle_in))),
			Point(xn1 - (size_y * Math::Sin(angle_in)), yn1 + (size_y * Math::Cos(angle_in)))
		};
		return cps;
	}
}

// Overload 2: Rotates the given image by the specified angle about its central point and
// returns the location of the top-left corner of the resulting image.

System::Drawing::Point Rotate(Image *img, double angle_in, float cx, float cy)
{
	double r, angle_base, size_x, size_y;
	size_x = img->get_Width();
	size_y = img->get_Height();
	angle_in *= Math::PI / 180;
	r = Math::Sqrt(Math::Pow(size_x / 2, 2) + Math::Pow(size_y / 2, 2));
	angle_base = Math::Atan(size_y/size_x);
	Point cps = Point(cx - (r * Math::Cos(angle_in + angle_base)), cy - (r * Math::Sin(angle_in + angle_base)));
	return cps;
}

// Overload 3: Rotates the given image by the specified angle about its central point and
// draws it in the specified container with its centre at a specific point.
void Rotate(Image * img, Control * container, double angle_in, float cx, float cy)
{
	Graphics *draw = container->CreateGraphics();
	double r, angle_base, size_x, size_y, xn1, yn1;
	size_x = img->get_Width();
	size_y = img->get_Height();
	angle_in *= Math::PI / 180;
	r = Math::Sqrt(Math::Pow(size_x / 2, 2) + Math::Pow(size_y / 2, 2));
	angle_base = Math::Atan(size_y/size_x);
	xn1 = cx - (r * Math::Cos(angle_in + angle_base));
	yn1 = cy - (r * Math::Sin(angle_in + angle_base));
	Point cps[] =
	{
		Point(xn1, yn1),
		Point(xn1 + (size_x * Math::Cos(angle_in)), yn1 + (size_x * Math::Sin(angle_in))),
		Point(xn1 - (size_y * Math::Sin(angle_in)), yn1 + (size_y * Math::Cos(angle_in)))
	};
	draw->DrawImage(img, cps);
}

// Overload 4: Rotates the given image by the specified angle about its central point and
// maps it to the specified Graphics object with its centre at a specific point.
void Rotate(Image * img, Graphics * draw, double angle_in, float cx, float cy)
{
	double r, angle_base, size_x, size_y, xn1, yn1;
	size_x = img->get_Width();
	size_y = img->get_Height();
	angle_in *= Math::PI / 180;
	r = Math::Sqrt(Math::Pow(size_x / 2, 2) + Math::Pow(size_y / 2, 2));
	angle_base = Math::Atan(size_y/size_x);
	xn1 = cx - (r * Math::Cos(angle_in + angle_base));
	yn1 = cy - (r * Math::Sin(angle_in + angle_base));
	Point cps[] =
	{
		Point(xn1, yn1),
		Point(xn1 + (size_x * Math::Cos(angle_in)), yn1 + (size_x * Math::Sin(angle_in))),
		Point(xn1 - (size_y * Math::Sin(angle_in)), yn1 + (size_y * Math::Cos(angle_in)))
	};
	draw->DrawImage(img, cps);
}
