// This file implements the IInputObject Interface and Gateway for Python.
// Generated by makegw.py

#include "shell_pch.h"
#include "PyIOleWindow.h"
#include "PyIInputObject.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIInputObject::PyIInputObject(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIInputObject::~PyIInputObject() {}

/* static */ IInputObject *PyIInputObject::GetI(PyObject *self) { return (IInputObject *)PyIOleWindow::GetI(self); }

// @pymethod |PyIInputObject|TranslateAccelerator|Description of TranslateAccelerator.
PyObject *PyIInputObject::TranslateAcceleratorIO(PyObject *self, PyObject *args)
{
    IInputObject *pISV = GetI(self);
    if (pISV == NULL)
        return NULL;
    MSG msg;
    PyObject *obpmsg;
    // @pyparm tuple|pmsg||Description for pmsg
    if (!PyArg_ParseTuple(args, "O:TranslateAcceleratorIO", &obpmsg))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (bPythonIsHappy && !PyObject_AsMSG(obpmsg, &msg))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pISV->TranslateAcceleratorIO(&msg);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pISV, IID_IInputObject);
    return PyLong_FromLong(hr);
}

// @pymethod |PyIInputObject|UIActivate|Description of UIActivate.
PyObject *PyIInputObject::UIActivateIO(PyObject *self, PyObject *args)
{
    IInputObject *pISV = GetI(self);
    if (pISV == NULL)
        return NULL;
    // @pyparm int|uState||Description for uState
    UINT uState;
    PyObject *obMsg;
    if (!PyArg_ParseTuple(args, "iO:UIActivateIO", &uState, &obMsg))
        return NULL;
    MSG msg, *pMsg;
    if (obMsg == Py_None) {
        pMsg = NULL;
    }
    else {
        if (!PyObject_AsMSG(obMsg, &msg))
            return NULL;
        pMsg = &msg;
    }
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pISV->UIActivateIO(uState, pMsg);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pISV, IID_IInputObject);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIInputObject|HasFocusIO|Description of Refresh.
PyObject *PyIInputObject::HasFocusIO(PyObject *self, PyObject *args)
{
    IInputObject *pISV = GetI(self);
    if (pISV == NULL)
        return NULL;
    if (!PyArg_ParseTuple(args, ":HasFocusIO"))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pISV->HasFocusIO();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pISV, IID_IInputObject);
    return PyBool_FromLong(hr == S_OK);
}

// @object PyIInputObject|Description of the interface
static struct PyMethodDef PyIInputObject_methods[] = {
    {"TranslateAcceleratorIO", PyIInputObject::TranslateAcceleratorIO,
     1},  // @pymeth TranslateAccelerator|Description of TranslateAccelerator
    {"UIActivateIO", PyIInputObject::UIActivateIO, 1},  // @pymeth UIActivate|Description of UIActivate
    {"HasFocusIO", PyIInputObject::HasFocusIO, 1},      // @pymeth HasFocusIO|Description of Refresh
    {NULL}};

PyComTypeObject PyIInputObject::type("PyIInputObject", &PyIOleWindow::type, sizeof(PyIInputObject),
                                     PyIInputObject_methods, GET_PYCOM_CTOR(PyIInputObject));
// ---------------------------------------------------
//
// Gateway Implementation

STDMETHODIMP PyGInputObject::TranslateAcceleratorIO(
    /* [in] */ MSG *pmsg)
{
    PY_GATEWAY_METHOD;
    PyObject *obpmsg = PyObject_FromMSG(pmsg);
    if (obpmsg == NULL)
        return MAKE_PYCOM_GATEWAY_FAILURE_CODE("TranslateAcceleratorIO");
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("TranslateAcceleratorIO", &result, "(O)", obpmsg);
    Py_DECREF(obpmsg);
    if (FAILED(hr))
        return hr;
    // Process the Python results, and convert back to the real params
    if (PyLong_Check(result) || PyLong_Check(result))
        hr = PyLong_AsLong(result);
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGInputObject::UIActivateIO(
    /* [in] */ BOOL uState,
    /* [in] */ MSG *pmsg)
{
    PY_GATEWAY_METHOD;
    PyObject *obpmsg = PyObject_FromMSG(pmsg);
    if (obpmsg == NULL)
        return MAKE_PYCOM_GATEWAY_FAILURE_CODE("UIActivateIO");
    HRESULT hr = InvokeViaPolicy("UIActivateIO", NULL, "iN", uState, obpmsg);
    return hr;
}

STDMETHODIMP PyGInputObject::HasFocusIO(void)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("HasFocusIO", &result);
    if (SUCCEEDED(hr))
        hr = PyObject_IsTrue(result) ? S_OK : S_FALSE;
    Py_XDECREF(result);
    return hr;
}
