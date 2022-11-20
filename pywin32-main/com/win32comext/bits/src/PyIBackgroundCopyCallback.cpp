// This file implements the IBackgroundCopyCallback Gateway for Python.
// Generated by makegw.py

#include "bits_pch.h"
#include "PyIBackgroundCopyCallback.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Gateway Implementation
STDMETHODIMP PyGBackgroundCopyCallback::JobTransferred(
    /* [in] */ IBackgroundCopyJob *pJob)
{
    PY_GATEWAY_METHOD;
    PyObject *obpJob;
    obpJob = PyCom_PyObjectFromIUnknown(pJob, IID_IBackgroundCopyJob, TRUE);
    HRESULT hr = InvokeViaPolicy("JobTransferred", NULL, "O", obpJob);
    Py_XDECREF(obpJob);
    return hr;
}

STDMETHODIMP PyGBackgroundCopyCallback::JobError(
    /* [in] */ IBackgroundCopyJob *pJob,
    /* [in] */ IBackgroundCopyError *pError)
{
    PY_GATEWAY_METHOD;
    PyObject *obpJob;
    PyObject *obpError;
    obpJob = PyCom_PyObjectFromIUnknown(pJob, IID_IBackgroundCopyJob, TRUE);
    obpError = PyCom_PyObjectFromIUnknown(pError, IID_IBackgroundCopyError, TRUE);
    HRESULT hr = InvokeViaPolicy("JobError", NULL, "OO", obpJob, obpError);
    Py_XDECREF(obpJob);
    Py_XDECREF(obpError);
    return hr;
}

STDMETHODIMP PyGBackgroundCopyCallback::JobModification(
    /* [in] */ IBackgroundCopyJob *pJob,
    /* [in] */ DWORD dwReserved)
{
    PY_GATEWAY_METHOD;
    PyObject *obpJob;
    obpJob = PyCom_PyObjectFromIUnknown(pJob, IID_IBackgroundCopyJob, TRUE);
    HRESULT hr = InvokeViaPolicy("JobModification", NULL, "Ol", obpJob, dwReserved);
    Py_XDECREF(obpJob);
    return hr;
}
