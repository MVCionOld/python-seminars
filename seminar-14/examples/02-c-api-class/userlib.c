#define PY_SSIZE_T_CLEAN  //  необходимо для использования z#
#include <python3.8/Python.h>
#include "structmember.h"

typedef struct {
  PyObject_HEAD;
  PyObject* first_name;
  PyObject* last_name;
  int age;
} UserPyClass;

PyTypeObject py_user_pyclass = {
    /* https://docs.python.org/3/c-api/structures.html#c.PyVarObject_HEAD_INIT */
    PyVarObject_HEAD_INIT(NULL, 0)
};

static void
UserPyClass_dealloc(UserPyClass* self) {
    Py_XDECREF(self->first_name);
    Py_XDECREF(self->last_name);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject*
UserPyClass_new(
    PyTypeObject* type,
    PyObject* args,
    PyObject* kwargs
) {
    UserPyClass* self;
    self = (UserPyClass *) type->tp_alloc(type, 0);

    if (self != NULL) {
        self->first_name = PyUnicode_FromString("");
        if (self->first_name == NULL) {
            Py_DECREF(self);
            return NULL;
        }

        self->last_name = PyUnicode_FromString("");
        if (self->last_name == NULL) {
            Py_DECREF(self);
            return NULL;
        }

        self->age = 0;
    }

    return (PyObject *) self;
}

static int
UserPyClass_init(
    UserPyClass* self,
    PyObject* args,
    PyObject* kwargs
) {
    static char *kwargs_list[] = {"first_name", "last_name", "age", NULL};
    PyObject* first_name = NULL;
    PyObject* last_name = NULL;
    PyObject* tmp;

    if (!PyArg_ParseTupleAndKeywords(
                    args,
                    kwargs,
                    "|OOi",
                    kwargs_list,
                    &first_name,
                    &last_name,
                    &self->age)) {
        return -1;  // should return either 0 on success or -1 on error
    }

    if (first_name) {
        tmp = self->first_name;
        Py_INCREF(first_name);
        self->first_name = first_name;
        Py_XDECREF(tmp);
    }

    if (last_name) {
        tmp = self->last_name;
        Py_INCREF(last_name);
        self->last_name = last_name;
        Py_XDECREF(tmp);
    }

    return 0;  // should return either 0 on success or -1 on error
}

/* Python equivalent:
 *
 * def get_full_name(self):
 *     return "%s %s" % (self.first, self.last)
 */
static PyObject*
UserPyClass_get_full_name(
    UserPyClass *self,
    PyObject* Py_UNUSED(ignored)
) {
    if (self->first_name == NULL) {
        PyErr_SetString(PyExc_AttributeError, "first_name");
        return NULL;
    }

    if (self->last_name == NULL) {
        PyErr_SetString(PyExc_AttributeError, "last_name");
        return NULL;
    }

    return PyUnicode_FromFormat(
        "%S %S",
        self->first_name,
        self->last_name
    );
}

/* https://docs.python.org/3/c-api/structures.html#c.PyMemberDef */
static PyMemberDef
UserPyClass_members[] = {
    {
        "first_name",
        T_OBJECT_EX,
        offsetof(UserPyClass, first_name),
        0,
        "first name"
    },
    {
        "last_name",
        T_OBJECT_EX,
        offsetof(UserPyClass, last_name),
        0,
        "last name"
    },
    {
        "age",
        T_INT,
        offsetof(UserPyClass, age),
        0,
        "user age"
    },
    {NULL}  /* Sentinel */
};

static PyMethodDef UserPyClass_methods[] = {
    {
        "get_full_name",
        (PyCFunction) UserPyClass_get_full_name,
        METH_NOARGS,
        "Return the name, combining the first and last name"
    },
    {NULL, NULL, 0, NULL}  /* Sentinel */
};

void
UserPyClass_prepare_type() {
    PyTypeObject* o = &py_user_pyclass;
    o->tp_name = "UserPyClass";
    o->tp_basicsize = sizeof(UserPyClass);
    o->tp_dealloc = (destructor) UserPyClass_dealloc;
    o->tp_flags = Py_TPFLAGS_DEFAULT;
    o->tp_doc = "Simple User class\n";
    o->tp_methods = UserPyClass_methods;
    o->tp_init = (initproc) UserPyClass_init;
    o->tp_new = UserPyClass_new;
    if (PyType_Ready(o) < 0) {
        Py_FatalError("Can't initialize 'UserPyClass'");
    }
}

static struct PyModuleDef
mod_def = {
    PyModuleDef_HEAD_INIT,
    "userlib",
    "Simple User class module",
    -1,
    NULL
};

// Инициализация модуля
PyMODINIT_FUNC PyInit_userlib(void) {
    PyObject* mod = PyModule_Create(&mod_def);
    UserPyClass_prepare_type();
    Py_INCREF(&py_user_pyclass);
    PyModule_AddObject(mod, "UserPyClass", (PyObject*)&py_user_pyclass);
    return mod;
}