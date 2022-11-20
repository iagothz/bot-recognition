// This file declares the IPropertyEnumType Interface and Gateway for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration

class PyIPropertyEnumType : public PyIUnknown {
   public:
    MAKE_PYCOM_CTOR(PyIPropertyEnumType);
    static IPropertyEnumType *GetI(PyObject *self);
    static PyComTypeObject type;

    // The Python methods
    static PyObject *GetEnumType(PyObject *self, PyObject *args);
    static PyObject *GetValue(PyObject *self, PyObject *args);
    static PyObject *GetRangeMinValue(PyObject *self, PyObject *args);
    static PyObject *GetRangeSetValue(PyObject *self, PyObject *args);
    static PyObject *GetDisplayText(PyObject *self, PyObject *args);

   protected:
    PyIPropertyEnumType(IUnknown *pdisp);
    ~PyIPropertyEnumType();
};
