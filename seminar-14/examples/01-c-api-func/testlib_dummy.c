#include <stdio.h>
#include <Python.h>

// Парсинг позиционных аргументов в лоб
static PyObject*
compose_impl(
    PyObject* /* указатель на модуль */ self,
    PyObject* /* все позиционные аргументы */ args
) {
    if (PyTuple_Size(args) != 2) {
        const char* message = "C API pyfunc arguments mismatch\n";
        /* выставляем ошибку в глобальную переменную */
        PyErr_SetString(
            /* PyObject* type = */PyExc_TypeError,
            /* const char* message = */message
        );
        fprintf(stderr, "%s", message);
        /* возвращаемый NULL - признак ошибки, не путать с None */
        return NULL;
    }

    long int integer;
    char* string;

    /* int PyArg_ParseTuple(PyObject *args, const char *format, ...) */
    /* "ls" - формат-строка, наподобие scanf/printf
     * "l" - long int
     * "s" - char*
     * ...
     * reference: https://docs.python.org/3/c-api/arg.html
     */
    if (!PyArg_ParseTuple(args, "ls", &integer, &string)) {
        return NULL;
    }

    /* PyObject* Py_BuildValue(const char *format, ...) */
    return Py_BuildValue("ls", integer, string);
}

/* список функций модуля (может быть несколько)
 * задается в виде массива структур PyMethodDef
 * https://docs.python.org/3/c-api/structures.html#c.PyMethodDef
 */
static PyMethodDef
methods[] = {
    {
        /* имя функции в Python-модуле */ "compose",
        /* указатель на функцию в C API */ compose_impl,
        /* METH_VARARGS - принимает позиционные аргументы*/ METH_VARARGS,
        /* строчка с help-информации (docstring) */ "Docstring for function 'compose(...)'"
    },
    {NULL, NULL, 0, NULL} // признак конца массива (like \0 в zero-terminated string)
};

/* Описание модуля
 * https://docs.python.org/3/c-api/module.html#c.PyModuleDef
 */
static struct PyModuleDef
mod = {
    /* must-have macro */PyModuleDef_HEAD_INIT,
    /* имя модуля */"testlib",
    /* строчка с help-информации (docstring) */"testlib module with dummy arg parsing",
    /* один модуль может использовать несколько интерпретаторов (размер shm), -1 -> запретить */-1,
    /* список методов модуля */methods
};

/* Инициализация модуля
 * имя функции должно быть PyInit_<ИМЯ МОДУЛЯ>
 */
PyMODINIT_FUNC PyInit_testlib(void) {
    return PyModule_Create(&mod);
}