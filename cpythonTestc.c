#define PY_SSIZE_T_CLEAN
// #include "/usr/include/python3.12/Python.h"
#include <Python.h>
#include <stdio.h>

PyObject *add(PyObject *self, PyObject *args) {
    int x;
    int y;

    PyArg_ParseTuple(args, "ii", &x, &y);

    return PyLong_FromLong((long)(x + y));


}

static PyMethodDef methods[] = {
    { "add", add, METH_VARARGS, "Adds two numbers!" },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef cpythonTestc = {
    PyModuleDef_HEAD_INIT,
    "__name__",
    "__doc__",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_cpythonTestc()
{
    
    int sts;
    printf("Hello world! \n");
    return PyModule_Create(&cpythonTestc);
}