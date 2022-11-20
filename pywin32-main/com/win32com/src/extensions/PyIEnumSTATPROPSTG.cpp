// This file implements the IEnumSTATPROPSTG Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"
#include "PythonCOM.h"
#include "PythonCOMServer.h"

#ifndef NO_PYCOM_ENUMSTATPROPSTG

#include "PyIEnumSTATPROPSTG.h"

// @doc - This file contains autoduck documentation

// ---------------------------------------------------
//
// Interface Implementation

PyIEnumSTATPROPSTG::PyIEnumSTATPROPSTG(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIEnumSTATPROPSTG::~PyIEnumSTATPROPSTG() {}

/* static */ IEnumSTATPROPSTG *PyIEnumSTATPROPSTG::GetI(PyObject *self)
{
    return (IEnumSTATPROPSTG *)PyIUnknown::GetI(self);
}

// @pymethod object|PyIEnumSTATPROPSTG|Next|Retrieves a specified number of items in the enumeration sequence.
PyObject *PyIEnumSTATPROPSTG::Next(PyObject *self, PyObject *args)
{
    long celt = 1;
    // @pyparm int|num|1|Number of items to retrieve.
    if (!PyArg_ParseTuple(args, "|l:Next", &celt))
        return NULL;

    IEnumSTATPROPSTG *pIESTATPROPSTG = GetI(self);
    if (pIESTATPROPSTG == NULL)
        return NULL;

    STATPROPSTG *rgVar = new STATPROPSTG[celt];
    if (rgVar == NULL) {
        PyErr_SetString(PyExc_MemoryError, "allocating result STATPROPSTGs");
        return NULL;
    }

    int i;
    /*	for ( i = celt; i--; )
            // *** possibly init each structure element???
    */

    ULONG celtFetched = 0;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIESTATPROPSTG->Next(celt, rgVar, &celtFetched);
    PY_INTERFACE_POSTCALL;
    if (HRESULT_CODE(hr) != ERROR_NO_MORE_ITEMS && FAILED(hr)) {
        delete[] rgVar;
        return PyCom_BuildPyException(hr);
    }

    PyObject *result = PyTuple_New(celtFetched);
    if (result != NULL) {
        for (i = celtFetched; i--;) {
            PyObject *ob =
                Py_BuildValue("NkH", PyWinObject_FromWCHAR(rgVar[i].lpwstrName), rgVar[i].propid, rgVar[i].vt);
            if (ob == NULL) {
                Py_DECREF(result);
                result = NULL;
                break;
            }
            PyTuple_SET_ITEM(result, i, ob);
        }
    }

    for (i = celtFetched; i--;) CoTaskMemFree(rgVar[i].lpwstrName);

    delete[] rgVar;
    return result;
}

// @pymethod |PyIEnumSTATPROPSTG|Skip|Skips over the next specified elementes.
PyObject *PyIEnumSTATPROPSTG::Skip(PyObject *self, PyObject *args)
{
    long celt;
    if (!PyArg_ParseTuple(args, "l:Skip", &celt))
        return NULL;

    IEnumSTATPROPSTG *pIESTATPROPSTG = GetI(self);
    if (pIESTATPROPSTG == NULL)
        return NULL;

    PY_INTERFACE_PRECALL;
    HRESULT hr = pIESTATPROPSTG->Skip(celt);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr);

    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIEnumSTATPROPSTG|Reset|Resets the enumeration sequence to the beginning.
PyObject *PyIEnumSTATPROPSTG::Reset(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":Reset"))
        return NULL;

    IEnumSTATPROPSTG *pIESTATPROPSTG = GetI(self);
    if (pIESTATPROPSTG == NULL)
        return NULL;

    PY_INTERFACE_PRECALL;
    HRESULT hr = pIESTATPROPSTG->Reset();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr);

    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod <o PyIEnumSTATPROPSTG>|PyIEnumSTATPROPSTG|Clone|Creates another enumerator that contains the same
// enumeration state as the current one
PyObject *PyIEnumSTATPROPSTG::Clone(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":Clone"))
        return NULL;

    IEnumSTATPROPSTG *pIESTATPROPSTG = GetI(self);
    if (pIESTATPROPSTG == NULL)
        return NULL;

    IEnumSTATPROPSTG *pClone;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIESTATPROPSTG->Clone(&pClone);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr);

    return PyCom_PyObjectFromIUnknown(pClone, IID_IEnumSTATPROPSTG, FALSE);
}

// @object PyIEnumSTATPROPSTG|A Python interface to IEnumSTATPROPSTG
static struct PyMethodDef PyIEnumSTATPROPSTG_methods[] = {
    {"Next", PyIEnumSTATPROPSTG::Next,
     1},  // @pymeth Next|Retrieves a specified number of items in the enumeration sequence.
    {"Skip", PyIEnumSTATPROPSTG::Skip, 1},    // @pymeth Skip|Skips over the next specified elementes.
    {"Reset", PyIEnumSTATPROPSTG::Reset, 1},  // @pymeth Reset|Resets the enumeration sequence to the beginning.
    {"Clone", PyIEnumSTATPROPSTG::Clone,
     1},  // @pymeth Clone|Creates another enumerator that contains the same enumeration state as the current one.
    {NULL}};

PyComEnumTypeObject PyIEnumSTATPROPSTG::type("PyIEnumSTATPROPSTG", &PyIUnknown::type, sizeof(PyIEnumSTATPROPSTG),
                                             PyIEnumSTATPROPSTG_methods, GET_PYCOM_CTOR(PyIEnumSTATPROPSTG));

// ---------------------------------------------------
//
// Gateway Implementation
STDMETHODIMP PyGEnumSTATPROPSTG::Next(
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ STATPROPSTG __RPC_FAR *rgVar,
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
    PyObject *obname;
    for (i = 0; i < len; ++i) {
        TmpPyObject ob = PySequence_GetItem(result, i);
        if (ob == NULL)
            goto error;

        if (!PyArg_ParseTuple(ob, "OkH", &obname, &rgVar[i].propid, &rgVar[i].vt) ||
            !PyWinObject_AsTaskAllocatedWCHAR(obname, &rgVar[i].lpwstrName, TRUE)) {
            Py_DECREF(result);
            for (; i--;) CoTaskMemFree(rgVar[i].lpwstrName);
            return PyCom_SetCOMErrorFromPyException(IID_IEnumSTATPROPSTG);
        }
    }

    Py_DECREF(result);

    return len < (int)celt ? S_FALSE : S_OK;

error:
    PyErr_Clear();  // just in case
    Py_DECREF(result);
    return PyCom_HandleIEnumNoSequence(IID_IEnumSTATPROPSTG);
}

STDMETHODIMP PyGEnumSTATPROPSTG::Skip(
    /* [in] */ ULONG celt)
{
    PY_GATEWAY_METHOD;
    return InvokeViaPolicy("Skip", NULL, "i", celt);
}

STDMETHODIMP PyGEnumSTATPROPSTG::Reset(void)
{
    PY_GATEWAY_METHOD;
    return InvokeViaPolicy("Reset");
}

STDMETHODIMP PyGEnumSTATPROPSTG::Clone(
    /* [out] */ IEnumSTATPROPSTG __RPC_FAR *__RPC_FAR *ppEnum)
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
        return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumSTATPROPSTG);
    }

    /*
    ** Get the IUnknown out of the thing. note that the Python ob maintains
    ** a reference, so we don't have to explicitly AddRef() here.
    */
    IUnknown *punk = ((PyIUnknown *)result)->m_obj;
    if (!punk) {
        /* damn. the object was released. */
        Py_DECREF(result);
        return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumSTATPROPSTG);
    }

    /*
    ** Get the interface we want. note it is returned with a refcount.
    ** This QI is actually going to instantiate a PyGEnumSTATPROPSTG.
    */
    hr = punk->QueryInterface(IID_IEnumSTATPROPSTG, (LPVOID *)ppEnum);

    /* done with the result; this DECREF is also for <punk> */
    Py_DECREF(result);

    return PyCom_CheckIEnumNextResult(hr, IID_IEnumSTATPROPSTG);
}

#endif  // NO_PYCOM_ENUMSTATPROPSTG
