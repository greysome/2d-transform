#include <stdio.h>
#include <math.h>
#include <cairo.h>

#define f1(x,y) sin(x)
#define f2(x,y) y+sin(x)
#define dom_xmin -5
#define dom_xmax 5
#define dom_ymin -5
#define dom_ymax 5
#define codom_xmin -5
#define codom_xmax 5
#define codom_ymin -5
#define codom_ymax 5
#define gridlinegap 0.5
#define samplegap 0.1

#define tsenable 1
#define ts_xmin -2
#define ts_xmax 2
#define ts_ymin -2
#define ts_ymax 2
#define tsgap 0.4

#define ts_startsize 1
#define ts_endsize 3
#define ts_startr 255
#define ts_startg 0
#define ts_startb 0
#define ts_endr 0
#define ts_endg 0
#define ts_endb 255

#define pdfsize 100
#define outputfile "out.pdf"


cairo_surface_t *cairo_pdf_surface_create(const char *filename,
        double width_in_points, double height_in_points);
cairo_surface_t *surface;
cairo_t *cr;
double pair[2];

void cartesian_to_cairo_coords(double x, double y) {
        double tx = (x-codom_xmin)/(codom_xmax-codom_xmin);
        double ty = (y-codom_ymax)/(codom_ymin-codom_ymax);
        pair[0] = tx * pdfsize;
        pair[1] = ty * pdfsize;
}

int main() {
        surface = cairo_pdf_surface_create(outputfile, pdfsize, pdfsize);
        cr = cairo_create(surface);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 0.1);

        double xcur, ycur;
        int n = dom_xmin / gridlinegap;
        xcur = n * gridlinegap;

        while (xcur <= dom_xmax) {
                ycur = dom_ymin;
                cartesian_to_cairo_coords(f1(xcur,ycur), f2(xcur,ycur));
                cairo_move_to(cr, pair[0], pair[1]);
                while (ycur <= dom_ymax) {
                        cartesian_to_cairo_coords(f1(xcur,ycur), f2(xcur,ycur));
                        cairo_line_to(cr, pair[0], pair[1]);
                        ycur += samplegap;
                }

                cairo_stroke(cr);
                xcur += gridlinegap;
        }


        n = dom_ymin / gridlinegap;
        ycur = n * gridlinegap;
        while (ycur <= dom_ymax) {
                xcur = dom_xmin;
                cartesian_to_cairo_coords(f1(xcur,ycur), f2(xcur,ycur));
                cairo_move_to(cr, pair[0], pair[1]);
                while (xcur <= dom_xmax) {
                        cartesian_to_cairo_coords(f1(xcur,ycur), f2(xcur,ycur));
                        cairo_line_to(cr, pair[0], pair[1]);
                        xcur += samplegap;
                }
                cairo_stroke(cr);
                ycur += gridlinegap;
        }

        if (tsenable) {
                double curx, cury;
                double tx, ty, r, g, b, size;
                curx = ts_xmin;
                while (curx <= ts_xmax) {
                        cury = ts_ymin;
                        while (cury <= ts_ymax) {
                                tx = (curx-ts_xmin)/(ts_xmax-ts_xmin);
                                ty = (cury-ts_ymin)/(ts_ymax-ts_ymin);
                                r = ((1-ty)*ts_startr + ty*ts_endr) / 255;
                                g = ((1-ty)*ts_startg + ty*ts_endg) / 255;
                                b = ((1-ty)*ts_startb + ty*ts_endb) / 255;
                                size = (1-tx)*ts_startsize + tx*ts_endsize;
                                cairo_set_source_rgba(cr, r, g, b, 0.5);
                                cartesian_to_cairo_coords(f1(curx,cury), f2(curx, cury));
                                cairo_arc(cr, pair[0], pair[1], size, 0, 2*M_PI);
                                cairo_fill(cr);

                                cury += tsgap;
                        }
                        curx += tsgap;
                }

        }

        cairo_destroy(cr);
        cairo_surface_destroy(surface);
        return 0;

}

