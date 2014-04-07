/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Fri  4 Apr 15:02:59 2014 CEST
 *
 * @brief Bindings to bob::ip color converters
 */

#ifdef NO_IMPORT_ARRAY
#undef NO_IMPORT_ARRAY
#endif
#include <xbob.blitz/capi.h>
#include <xbob.blitz/cleanup.h>
#include <xbob.extension/documentation.h>

extern PyObject* PyBobIpDraw_Point(PyObject*, PyObject* args, PyObject* kwds);
static xbob::extension::FunctionDoc s_point = xbob::extension::FunctionDoc(
    "point",

    "Draws a point in the given (gray-scale or color) image.",

    "This method can draw a point in either gray-scale (2D) or color images. "
    "Images have to be :py:class:`numpy.ndarray`'s with either ``uint8``, "
    "``uint16`` or ``float64`` data type. Trying to access outside the image "
    "range will raise a :py:class:`RuntimeError`.\n"
    "\n"
    "In case you pass a 2D array representing a gray-scale image, this function "
    "expects you pass a single scalar as a value for the input parameter "
    "``color``. In the case you pass a 3D array (color image), then the color "
    "parameter should be set to a tuple contanining 3 scalars representing the "
    "levels for each of the color components (red, green and blue)\n"
    "\n"
    "Color images are expected to be represented using the first dimension for "
    "the color planes: ``(3, height, width)``. Images are modified in place.\n"
    )

    .add_prototype("image, y, x, color")
    .add_parameter("image", "array (uint8|uint16|float64, 3D)", "Input array containing an image with the shape ``(height, width)`` (for gray-scale images) or ``(3, height, width)`` (for color images)")
    .add_parameter("y, x", "int", "Index (0-based) pointing to the location on the image that the pixel is going to be drawn.")
    .add_parameter("color", "scalar|tuple", "Color of the pixel. In case the input image is gray-scale (2D), this should be a single scalar. If the input image is colored (3D), then it should be a sequence containing 3 scalars, representing the levels of red, green and blue (in this order) of the pixel to be drawn.")
    ;

extern PyObject* PyBobIpDraw_TryPoint(PyObject*, PyObject* args, PyObject* kwds);
static xbob::extension::FunctionDoc s_try_point = xbob::extension::FunctionDoc(
    "try_point",

    "Tries to draw a point in the given (gray-scale or color) image.",

    "This method tries to draw a point in either gray-scale (2D) or color "
    "images. If the point is out of bounds, it is simply ignored and not "
    "drawn. The input of this method is identical to the input of "
    ":py:func:`point`, in this module. See its help message for details."
    )

    .add_prototype("image, y, x, color")
    .add_parameter("image", "array (uint8|uint16|float64, 3D)", "Input array containing an image with the shape ``(height, width)`` (for gray-scale images) or ``(3, height, width)`` (for color images)")
    .add_parameter("y, x", "int", "Index (0-based) pointing to the location on the image that the pixel is going to be drawn.")
    .add_parameter("color", "scalar|tuple", "Color of the pixel. In case the input image is gray-scale (2D), this should be a single scalar. If the input image is colored (3D), then it should be a sequence containing 3 scalars, representing the levels of red, green and blue (in this order) of the pixel to be drawn.")
    ;

/**
  def("draw_line", &draw_line, (arg("image"), arg("y1"), arg("x1"), arg("y2"), arg("x2"), arg("color")), "Draws a line between two points p1(x1,y1) and p2(x2,y2).  This function is based on the Bresenham's line algorithm and is highly optimized to be able to draw lines very quickly. There is no floating point arithmetic nor multiplications and divisions involved. Only addition, subtraction and bit shifting are used.\n\nThe line may go out of the image bounds in which case such points (lying outside the image boundary are ignored).\n\nReferences: http://en.wikipedia.org/wiki/Bresenham's_line_algorithm. This method supports both grayscale (2D) or color RGB (3D) images. Depending on your image type, select an appropriate color value: a single gray value for 2D grayscale images or a 3-tuple containing the RGB color to set during drawing.");
  def("draw_cross", &draw_cross, (arg("image"), arg("y"), arg("x"), arg("radius"), arg("color")), "Draws a cross with a given radius and color at the image. Uses the draw_line() primitive above. The cross will look like an 'x' and not like a '+'. To get a '+' sign, use the draw_cross_plus() variant. This method supports both grayscale (2D) or color RGB (3D) images. Depending on your image type, select an appropriate color value: a single gray value for 2D grayscale images or a 3-tuple containing the RGB color to set during drawing.");
  def("draw_cross_plus", &draw_cross_plus, (arg("image"), arg("y"), arg("x"), arg("radius"), arg("color")), "Draws a cross with a given radius and color at the image. Uses the draw_line() primitive above. The cross will look like an '+' and not like a 'x'. To get a 'x' sign, use the draw_cross() variant. This method supports both grayscale (2D) or color RGB (3D) images. Depending on your image type, select an appropriate color value: a single gray value for 2D grayscale images or a 3-tuple containing the RGB color to set during drawing.");
  def("draw_box", &draw_box, (arg("image"), arg("y"), arg("x"), arg("height"), arg("width"), arg("color")), "Draws a box at the image using the draw_line() primitive. This method supports both grayscale (2D) or color RGB (3D) images. Depending on your image type, select an appropriate color value: a single gray value for 2D grayscale images or a 3-tuple containing the RGB color to set during drawing.");
**/

static PyMethodDef module_methods[] = {
    {
      s_point.name(),
      (PyCFunction)PyBobIpDraw_Point,
      METH_VARARGS|METH_KEYWORDS,
      s_point.doc()
    },
    {
      s_try_point.name(),
      (PyCFunction)PyBobIpDraw_TryPoint,
      METH_VARARGS|METH_KEYWORDS,
      s_try_point.doc()
    },
    {0}  /* Sentinel */
};

PyDoc_STRVAR(module_docstr, "Bob image drawing utilitiles");

#if PY_VERSION_HEX >= 0x03000000
static PyModuleDef module_definition = {
  PyModuleDef_HEAD_INIT,
  XBOB_EXT_MODULE_NAME,
  module_docstr,
  -1,
  module_methods,
  0, 0, 0, 0
};
#endif

static PyObject* create_module (void) {

# if PY_VERSION_HEX >= 0x03000000
  PyObject* m = PyModule_Create(&module_definition);
# else
  PyObject* m = Py_InitModule3(XBOB_EXT_MODULE_NAME, module_methods, module_docstr);
# endif
  if (!m) return 0;
  auto m_ = make_safe(m); ///< protects against early returns

  if (PyModule_AddStringConstant(m, "__version__", XBOB_EXT_MODULE_VERSION) < 0)
    return 0;

  /* imports xbob.blitz C-API + dependencies */
  if (import_xbob_blitz() < 0) return 0;

  Py_INCREF(m);
  return m;

}

PyMODINIT_FUNC XBOB_EXT_ENTRY_NAME (void) {
# if PY_VERSION_HEX >= 0x03000000
  return
# endif
    create_module();
}
