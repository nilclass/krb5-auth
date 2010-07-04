#include "krb5_auth.h"

// Free function for the Krb5Auth::Krb5::Keytab class.
static void rkrb5_princ_free(RUBY_KRB5_PRINC* ptr){
  if(!ptr)
    return;

  free(ptr);
}

// Allocation function for the Krb5Auth::Krb5::Keytab class.
static VALUE rkrb5_princ_allocate(VALUE klass){
  RUBY_KRB5_PRINC* ptr = malloc(sizeof(RUBY_KRB5_PRINC));
  memset(ptr, 0, sizeof(RUBY_KRB5_PRINC));
  return Data_Wrap_Struct(klass, 0, rkrb5_princ_free, ptr);
}

/*
 * call-seq:
 *   Krb5Auth::Krb5::Principal.new
 *
 * Creates and returns a new Krb5::Principal object. If a block is provided
 * then it yields itself.
 *
 * Example:
 *
 *   principal1 = Krb5Auth::Krb5::Principal.new
 *
 *   principal2 = Krb5Auth::Krb5::Principal.new do |pr|
 *     pr.name = "Jon"
 *     pr.expire_time = Time.now + 20000
 *   end
 */
static VALUE rkrb5_princ_initialize(VALUE self){
  RUBY_KRB5_PRINC* ptr;
  Data_Get_Struct(self, RUBY_KRB5_PRINC, ptr); 

  if(rb_block_given_p())
    rb_yield(self);

  return self;
}

void Init_principal(){
  /* The Krb5Auth::Krb5::Principal class encapsulates a Kerberos principal. */
  cKrb5Principal = rb_define_class_under(cKrb5, "Principal", rb_cObject);

  // Allocation Function
  rb_define_alloc_func(cKrb5Principal, rkrb5_princ_allocate);

  // Constructor
  rb_define_method(cKrb5Principal, "initialize", rkrb5_princ_initialize, 0);

  // Attributes
  rb_define_attr(cKrb5Principal, "name", 1, 1);
  rb_define_attr(cKrb5Principal, "expire_time", 1, 1);
  rb_define_attr(cKrb5Principal, "last_password_change", 1, 1);
  rb_define_attr(cKrb5Principal, "password_expiration", 1, 1);
  rb_define_attr(cKrb5Principal, "max_life", 1, 1);
  rb_define_attr(cKrb5Principal, "mod_name", 1, 1);
  rb_define_attr(cKrb5Principal, "mod_date", 1, 1);
  rb_define_attr(cKrb5Principal, "attributes", 1, 1);
  rb_define_attr(cKrb5Principal, "vno", 1, 1);
  rb_define_attr(cKrb5Principal, "policy", 1, 1);
  rb_define_attr(cKrb5Principal, "max_renewable_life", 1, 1);
  rb_define_attr(cKrb5Principal, "last_success", 1, 1);
  rb_define_attr(cKrb5Principal, "last_failed", 1, 1);
  rb_define_attr(cKrb5Principal, "fail_auth_count", 1, 1);
}