#include <stdio.h>
#include <Python.h>

// Module method definition 'hello_world'
static PyObject*
hello_world(
    PyObject* /* указатель на модуль */ self,
    PyObject* /* все позиционные аргументы */ args
) {
    printf("Hello, world!\n");
    /* aka return None */
    Py_RETURN_NONE;
}

// Module method definition 'hello'
static PyObject*
hello(
    PyObject* /* указатель на модуль */ self,
    PyObject* /* все позиционные аргументы */ args
) {
    if (PyTuple_Size(args) != 1) {
        const char* message = "C API function 'hello': arguments number mismatch\n";
        /* выставляем ошибку в глобальную переменную */
        PyErr_SetString(
            /* PyObject* type = */PyExc_TypeError,
            /* const char* message = */message
        );
        /* возвращаемый NULL - признак ошибки, не путать с None */
        return NULL;
    }

    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        const char* message = "C API function 'hello': argument is not a str\n";
        /* выставляем ошибку в глобальную переменную */
        PyErr_SetString(
            /* PyObject* type = */PyExc_TypeError,
            /* const char* message = */message
        );
        /* возвращаемый NULL - признак ошибки, не путать с None */
        return NULL;
    }

    printf("Hello, %s!\n", name);

    /* aka return None */
    Py_RETURN_NONE;
}

// Method definition object for this extension, these arguments mean:
// ml_name: The name of the method
// ml_meth: Function pointer to the method implementation
// ml_flags: Flags indicating special features of this method, such as
//          accepting arguments, accepting keyword arguments, being a
//          class method, or being a static method of a class.
// ml_doc:  Contents of this method's docstring
static PyMethodDef
methods[] = {
    {
        "hello_world",
        hello_world,
        METH_NOARGS,
        "Print 'hello world' from a method defined in a C extension."
    },
    {
        "hello",
        hello,
        METH_VARARGS,
        "Print 'hello xxx' from a method defined in a C extension."
    },
    {NULL, NULL, 0, NULL} // Sentinel
};

// Module definition
// The arguments of this structure tell Python what to call your extension,
// what it's methods are and where to look for its method definitions
static struct PyModuleDef
mod = {
    PyModuleDef_HEAD_INIT,
    "hellolib",
    "A Python module that prints 'hello world' from C code.",
    -1,
    methods
};

// Module initialization
// Python calls this function when importing your extension. It is important
// that this function is named PyInit_[[your_module_name]] exactly, and matches
// the name keyword argument in setup.py's setup() call.
PyMODINIT_FUNC PyInit_hellolib(void) {
    return PyModule_Create(&mod);
}