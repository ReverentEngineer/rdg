#define PY_SSIZE_T_CLEAN
#include <Python.h>

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

    m = PyModule_Create(&rdg_module);
    if (m == NULL)
        return NULL;
    
    return m;
}

