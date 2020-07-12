#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <ctype.h>

#include "rdg.h"

typedef struct {
  PyObject_HEAD
  struct rdg* rdg;
} RDG;

static PyObject* RDG_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    RDG *self = NULL;
    self = (RDG*) type->tp_alloc(type, 0);
    return (PyObject *) self;
}

static void RDG_dealloc(RDG *self) {
    if (self->rdg) {
      rdg_free(self->rdg);
    }
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static int isrdgspecial(char c) {
  if (c == '[' || 
      c == ']' ||
      c == '(' ||
      c == ')' ||
      c == '|' ||
      c == '-' ||
      c == '.' ||
      c == '\\') 
    return 1;
  else
    return 0;
}

static char* encode_expression(const char* expression, Py_ssize_t length) {
  char* encoded = NULL;
  Py_ssize_t final_length = 0;
  char* output = NULL;
  for (Py_ssize_t i = 0; i < length; i++) {
    if (isalnum(expression[i]) || isrdgspecial(expression[i])) {
      final_length += 1;
    } else {
      final_length += 4;
    }
  }
  encoded = malloc(final_length + 1);
  output = encoded;
  for (Py_ssize_t i = 0; i < length; i++) {
    if (isalnum(expression[i]) || isrdgspecial(expression[i])) {
      *output = expression[i];
      output += 1;
    } else {
      sprintf(output, "\\x%02x", expression[i]); 
      output += 4;
    }
  }
  *output = 0;
  return encoded;
}

static int RDG_init(RDG *self, PyObject *args, PyObject *kwds) {
    const char* expression = NULL;
    Py_ssize_t length = -1;
    char *encoded = NULL;

    if (!PyArg_ParseTuple(args, "s#", &expression, &length)) {
      return -1;
    }

    if (length == 0) {
      PyErr_Format(PyExc_ValueError, "Need a non-empty string");
      return -1;
    }

    encoded = encode_expression(expression, length);

    self->rdg = rdg_new(encoded);

    free(encoded);

    return 0;
}

static PyObject* RDG_next(RDG* self) {
  unsigned char *data = NULL;
  size_t size = 0;

  rdg_generate(&data, &size, self->rdg);

  if (data == NULL || size == 0) {
    PyErr_Format(PyExc_StopIteration, "End of permutations");
    return NULL;
  }
  
  return PyBytes_FromStringAndSize((char*)data, size);
}


static PyTypeObject RDGType  = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "rdg.RDG",
    .tp_doc = "Regex data generator",
    .tp_basicsize = sizeof(RDG),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_iter = PyObject_SelfIter,
    .tp_iternext = (iternextfunc) RDG_next,
    .tp_new = RDG_new,
    .tp_init = (initproc) RDG_init,
    .tp_dealloc = (destructor) RDG_dealloc,
};

static struct PyModuleDef rdg_module = {
    PyModuleDef_HEAD_INIT,
    "rdg",
    NULL,
    -1, 
    NULL
};

PyMODINIT_FUNC
PyInit_rdg(void)
{
    PyObject *m;
    if (PyType_Ready(&RDGType) < 0) {
      return NULL;
    }

    m = PyModule_Create(&rdg_module);
    if (m == NULL) {
        return NULL;
    }

    Py_INCREF(&RDGType);
    if (PyModule_AddObject(m, "RDG", (PyObject *) &RDGType) < 0) {
        Py_DECREF(&RDGType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

