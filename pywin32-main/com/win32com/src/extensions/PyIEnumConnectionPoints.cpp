// This file implements the IEnumConnectionPoints Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"
#include "PythonCOM.h"
#include "PythonCOMServer.h"
#include "PyIEnumConnectionPoints.h"

// @doc - This file contains autoduck documentation

// ---------------------------------------------------
//
// Interface Implementation

PyIEnumConnectionPoints::PyIEnumConnectionPoints(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIEnumConnectionPoints::~PyIEnumConnectionPoints() {}

/* static */ IEnumConnectionPoints *PyIEnumConnectionPoints::GetI(PyObject *self)
{
    return (IEnumConnectionPoints *)PyIUnknown::GetI(self);
}

// @pymethod (<o PyIConnectionPoint>, ...)|PyIEnumConnectionPoints|Next|Retrieves a specified number of items in the
// enumeration sequence.
PyObject *PyIEnumConnectionPoints::Next(PyObject *self, PyObject *args)
{
    long celt = 1;
    // @pyparm int|num|1|Number of items to retrieve.
    if (!PyArg_ParseTuple(args, "|l:Next", &celt))
        return NULL;

    IEnumConnectionPoints *pIEConnections = GetI(self);
    if (pIEConnections == NULL)
        return NULL;

    IConnectionPoint **rgVar = new IConnectionPoint *[celt];
    if (rgVar == NULL) {
        PyErr_SetString(PyExc_MemoryError, "allocating result array");
        return NULL;
    }
    memset(rgVar, 0, sizeof(IConnectionPoint *) * celt);

    int i;
    ULONG celtFetched = 0;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIEConnections->Next(celt, rgVar, &celtFetched);
    PY_INTERFACE_POSTCALL;
    if (HRESULT_CODE(hr) != ERROR_NO_MORE_ITEMS && FAILED(hr)) {
        delete[] rgVar;
        return PyCom_BuildPyException(hr);
    }

    PyObject *result = PyTuple_New(celtFetched);
    if (result) {
        for (i = celtFetched; i--;) {
            PyObject *ob = PyCom_PyObjectFromIUnknown(rgVar[i], IID_IConnectionPoint, FALSE);
            rgVar[i] = NULL;
            if (ob == NULL) {
                Py_DECREF(result);
                result = NULL;
                break;
            }
            PyTuple_SET_ITEM(result, i, ob);
        }
    }
    for (i = celtFetched; i--;) PYCOM_RELEASE(rgVar[i]);
    delete[] rgVar;
    return result;
}

// @pymethod |PyIEnumConnectionPoints|Skip|Skips over the next specified elementes.
PyObject *PyIEnumConnectionPoints::Skip(PyObject *self, PyObject *args)
{
    long celt;
    if (!PyArg_ParseTuple(args, "l:Skip", &celt))
        return NULL;

    IEnumConnectionPoints *pIEConnections = GetI(self);
    if (pIEConnections == NULL)
        return NULL;

    PY_INTERFACE_PRECALL;
    HRESULT hr = pIEConnections->Skip(celt);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr);

    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIEnumConnectionPoints|Reset|Resets the enumeration sequence to the beginning.
PyObject *PyIEnumConnectionPoints::Reset(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":Reset"))
        return NULL;

    IEnumConnectionPoints *pIEConnections = GetI(self);
    if (pIEConnections == NULL)
        return NULL;

    PY_INTERFACE_PRECALL;
    HRESULT hr = pIEConnections->Reset();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr);

    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod <o PyIEnumConnectionPoints>|PyIEnumConnectionPoints|Clone|Creates another enumerator that contains the same
// enumeration state as the current one
PyObject *PyIEnumConnectionPoints::Clone(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":Clone"))
        return NULL;

    IEnumConnectionPoints *pIEConnections = GetI(self);
    if (pIEConnections == NULL)
        return NULL;

    IEnumConnectionPoints *pClone;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIEConnections->Clone(&pClone);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr);

    return PyCom_PyObjectFromIUnknown(pClone, IID_IEnumConnectionPoints, FALSE);
}

// @object PyIEnumConnectionPoints|A Python interface to IEnumConnectionPoints
static struct PyMethodDef PyIEnumConnectionPoints_methods[] = {
    {"Next", PyIEnumConnectionPoints::Next,
     1},  // @pymeth Next|Retrieves a specified number of items in the enumeration sequence.
    {"Skip", PyIEnumConnectionPoints::Skip, 1},    // @pymeth Skip|Skips over the next specified elementes.
    {"Reset", PyIEnumConnectionPoints::Reset, 1},  // @pymeth Reset|Resets the enumeration sequence to the beginning.
    {"Clone", PyIEnumConnectionPoints::Clone,
     1},  // @pymeth Clone|Creates another enumerator that contains the same enumeration state as the current one.
    {NULL}};

PyComEnumTypeObject PyIEnumConnectionPoints::type("PyIEnumConnectionPoints",
                                                  &PyIUnknown::type,  // @base PyIEnumConnectionPoints|PyIUnknown
                                                  sizeof(PyIEnumConnectionPoints), PyIEnumConnectionPoints_methods,
                                                  GET_PYCOM_CTOR(PyIEnumConnectionPoints));

// ---------------------------------------------------
//
// Gateway Implementation

STDMETHODIMP PyGEnumConnectionPoints::Next(
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ IConnectionPoint **rgVar,
    /* [out] */ ULONG __RPC_FAR *pCeltFetched)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("Next", &result, "i", celt);
    if (FAILED(hr))
        return hr;

    if (!PySequence_Check(result))
        goto error;
    Py_ssize_t len = PyObject_Length(result);
    if (len == -1 || !PyWin_is_ssize_dword(len))
        goto error;
    if (len > celt)
        len = celt;

    if (pCeltFetched)
        *pCeltFetched = (ULONG)len;

    int i;
    for (i = 0; i < len; ++i) {
        PyObject *ob = PySequence_GetItem(result, i);
        if (ob == NULL)
            goto error;

        if (!PyCom_InterfaceFromPyObject(ob, IID_IConnectionPoint, reinterpret_cast<void **>(&rgVar[i]), FALSE)) {
            Py_DECREF(result);
            return PyCom_SetCOMErrorFromPyException(IID_IEnumConnectionPoints);
        }
    }

    Py_DECREF(result);

    return len < (int)celt ? S_FALSE : S_OK;

error:
    PyErr_Clear();  // just in case
    Py_DECREF(result);
    return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumConnectionPoints);
}

STDMETHODIMP PyGEnumConnectionPoints::Skip(
    /* [in] */ ULONG celt)
{
    PY_GATEWAY_METHOD;
    return InvokeViaPolicy("Skip", NULL, "i", celt);
}

STDMETHODIMP PyGEnumConnectionPoints::Reset(void)
{
    PY_GATEWAY_METHOD;
    return InvokeViaPolicy("Reset");
}

STDMETHODIMP PyGEnumConnectionPoints::Clone(
    /* [out] */ IEnumConnectionPoints __RPC_FAR *__RPC_FAR *ppEnum)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("Clone", &result);
    if (FAILED(hr))
        return hr;

    /*
    ** Make sure we have the right kind of object: we should have some kind
    ** of IUnknown subclass wrapped into a PyIUnknown instance.
    */
    if (!PyIBase::is_object(result, &PyIUnknown::type)) {
        /* the wrong kind of object was returned to us */
        Py_DECREF(result);
        return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumConnectionPoints);
    }

    /*
    ** Get the IUnknown out of the thing. note that the Python ob maintains
    ** a reference, so we don't have to explicitly AddRef() here.
    */
    IUnknown *punk = ((PyIUnknown *)result)->m_obj;
    if (!punk) {
        /* damn. the object was released. */
        Py_DECREF(result);
        return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumConnectionPoints);
    }

    /*
    ** Get the interface we want. note it is returned with a refcount.
    ** This QI is actually going to instantiate a PyGEnumConnections.
    */
    Py_BEGIN_ALLOW_THREADS hr = punk->QueryInterface(IID_IEnumConnectionPoints, (LPVOID *)ppEnum);
    Py_END_ALLOW_THREADS

        /* done with the result; this DECREF is also for <punk> */
        Py_DECREF(result);

    return PyCom_SetCOMErrorFromSimple(hr, IID_IEnumConnectionPoints);
}
