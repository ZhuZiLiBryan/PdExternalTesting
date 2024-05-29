#include "m_pd.h"   

// Need static pointer of type t_class as main handle for class
static t_class *polybang_class;

// Pd source heavily dependent on structs that you pass along
typedef struct _polybang {
    //t_object must ALWAYS be first member of struct 
    t_object x_obj;
    t_int init_count, current_count;

    // Set creation arguments
    t_int mod_A, mod_B;
} t_polybang;

// Create function that acts as an initializer for class
void *polybang_new(void) {
    //pd_new returns generic pointer so need to typecast as t_polybang *
    t_polybang *x = (t_polybang *)pd_new(polybang_class);
    return (void *)x;
}

// Need function to set-up the class and call the initializer
//! MUST BE CALLED externalname_setup!

/*
 * below is the method header for class new
 * EXTERN t_class *class_new(t_symbol *name, t_newmethod newmethod,
 *   t_method freemethod, size_t size, int flags, t_atomtype arg1, ...);
 * 
 * t_symbol *name -> name that you type into Pd object to create
 *                   the external.  Can use gensym fcn to create this.
 * 
 * t_newmethod newmethod -> the initializing method we created earlier
 *                          has to be cast as t_newmethod
 * 
 * t_method freemethod -> function called whenever object is deleted from pd
 *                        for now, type 0 to indicate no freemethod
 * 
 * size_t size         -> size of memory this class will take up
 * 
 * int flags           -> manages appearance of object in Pd (object box or else)
 *                        for normal, just do CLASS_DEFAULT
 * 
 * t_atomtype arg1...  -> creation arguments 
 *                        (arguments used when creating the object, e.g. the 400 in osc 400)
 * 
 * WHEN DONE WITH ARGUMENTS, LAST ARG NEEDS TO BE 0 TO INDICATE NO MORE ARGUMENTS
 */
void polybang_setup(void) {
    polybang_class = class_new(gensym("polybang"), 
                               (t_newmethod)polybang_new,
                               0,
                               sizeof(t_polybang),
                               CLASS_DEFAULT,
                               A_DEFFLOAT,
                               A_DEFFLOAT,
                               0);
}