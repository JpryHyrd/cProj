#include <Python.h>
#include "matem.h"

static PyObject *py_k(PyObject *self, PyObject *args)
{
    double a, b, c, d, result;

    if(!PyArg_ParseTuple(args,"dddd", &a, &b, &c, &d))
        return NULL;

    result = _k(a, b, c, d);

    return Py_BuildValue("d", result);
}

static PyObject *py_pk(PyObject *self, PyObject *args)
{
    double result, n;

    if(!PyArg_ParseTuple(args,"d", &n))
        return NULL;

    result = _pk(n);

    return Py_BuildValue("d", result);
}

static PyObject *py_d(PyObject *self, PyObject *args)
{
    double result, a, b, c;

    if(!PyArg_ParseTuple(args,"ddd", &a, &b, &c))
        return NULL;

    result = _d(a, b, c);

    return Py_BuildValue("d", result);
}

static PyObject *py_lnv(PyObject *self, PyObject *args)
{
    double result, n, k;

    if(!PyArg_ParseTuple(args,"dd", &n, &k))
        return NULL;

    result = _lnv(n, k);

    return Py_BuildValue("d", result);
}

static PyObject *py_ntp(PyObject *self, PyObject *args)
{
    double result, a, b;

    if(!PyArg_ParseTuple(args,"dd", &a, &b))
        return NULL;

    result = _ntp(a, b);

    return Py_BuildValue("d", result);
}

static PyObject *py_summ(PyObject *self, PyObject *args)
{
    int result, n, k;

    if(!PyArg_ParseTuple(args,"ii", &n, &k))
        return NULL;

    result = _summ(n, k);

    return Py_BuildValue("i", result);
}

static PyMethodDef ownmod_methods[] = {
    {"k", py_k, METH_VARARGS, "Fibonacci function"}, // 
    {"pk", py_pk, METH_VARARGS, "Get PI function"}, // 
    {"d", py_d, METH_VARARGS, "Get E function"}, // 
    {"lnv", py_lnv, METH_VARARGS, "Get sin of current angle in degrees"}, // 
    {"ntp", py_ntp, METH_VARARGS, "Get Number to Power"}, 
    {"summ", py_summ, METH_VARARGS, "Get number of summ from n to k"},
    { NULL, NULL, 0, NULL }
};

static PyModuleDef simple_module = {
    PyModuleDef_HEAD_INIT,   
    "pmath",               
    "Python library to work with math's fuctions.", 
    -1,
    ownmod_methods          
};

PyMODINIT_FUNC PyInit_pmath(void)
{
      PyObject* m;
      m = PyModule_Create(&simple_module);
      if (m == NULL)
          return NULL;
      return m;
}
