#define PY_SSIZE_T_CLEAN  //  необходимо для использования z#

#include <stdio.h>
#include <python3.8/Python.h>

// Парсинг позиционных и именованных аргументов
static PyObject*
compose_impl(
    PyObject* /* указатель на модуль */ self,
    PyObject* /* все позиционные аргументы */ args,
    PyObject* /* все именованные аргументы */ kwargs
) {
    static const char* kwlist[] = {"integer", "string", NULL};

    long int integer = 0;
    char* string = "";
    Py_ssize_t string_len = 0;

    /* до | (пайпа) обязательные аргументы,
     * "l" - long int
     * "z#" - char* + size_t
     * ...
     * reference: https://docs.python.org/3/c-api/arg.html
     */
    if (!PyArg_ParseTupleAndKeywords(
            args,
            kwargs,
            "l|z#",
            (char**)kwlist,
            &integer,
            &string,
            &string_len
        )) {
        // ошибка уже выставлена функцией PyArg_ParseTupleAndKeywords
        return NULL;
    }

    /* PyObject* Py_BuildValue(const char *format, ...) */
    return Py_BuildValue("ls", integer, string);
    /*
     * пишем Py_RETURN_NONE; - вместо return-выражения, если функция не должна ничего возвращать
     */
}

/* список функций модуля (может быть несколько)
 * задается в виде массива структур PyMethodDef
 * https://docs.python.org/3/c-api/structures.html#c.PyMethodDef
 */
static PyMethodDef
    methods[] = {
    {
        /* имя функции в Python-модуле */ "compose",
        /* указатель на функцию в C API */ (PyCFunction)compose_impl,
        /* METH_KEYWORDS - принимает еще и именованные аргументы*/ METH_VARARGS | METH_KEYWORDS,
        // METH_NOARGS - если функция не принимает аргументов
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
    /* строчка с help-информации (docstring) */"testlib module with clever arg parsing",
    /* один модуль может использовать несколько интепретаторов (размер shm), -1 -> запретить */-1,
    /* список методов модуля */methods
};

/* Инициализация модуля
 * имя функции должно быть PyInit_<ИМЯ МОДУЛЯ>
 */
PyMODINIT_FUNC PyInit_testlib(void) {
    return PyModule_Create(&mod);
}
