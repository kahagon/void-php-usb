/*
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.0 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_0.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Keng-ichi Ahagon <oasynnoum@gmail.com>                      |
   +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#include "php_usb.h"

#if HAVE_USB

/* {{{ Resource destructors */
int le_usb_context;
void usb_context_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	libusb_context * resource = (libusb_context *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_device_handle;
void usb_device_handle_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	libusb_device_handle * resource = (libusb_device_handle *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_device;
void usb_device_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	libusb_device * resource = (libusb_device *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_device_list;
void usb_device_list_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	libusb_device ** resource = (libusb_device **)(rsrc->ptr);

	do {
            libusb_free_device_list(resource, 1);
            php_error(E_WARNING, "libusb_device list freed\n"); 
	} while (0);
}

/* }}} */

/* {{{ usb_functions[] */
function_entry usb_functions[] = {
	PHP_FE(usb_init            , usb_init_arg_info)
	PHP_FE(usb_exit            , usb_exit_arg_info)
	PHP_FE(usb_open_device_with_vid_pid, usb_open_device_with_vid_pid_arg_info)
	PHP_FE(usb_get_device      , usb_get_device_arg_info)
	PHP_FE(usb_get_device_descriptor, usb_get_device_descriptor_arg_info)
	PHP_FE(usb_get_config_descriptor, usb_get_config_descriptor_arg_info)
	PHP_FE(usb_get_active_config_descriptor, usb_get_active_config_descriptor_arg_info)
	PHP_FE(usb_get_config_descriptor_by_value, usb_get_config_descriptor_by_value_arg_info)
	PHP_FE(usb_get_string_descriptor_ascii, usb_get_string_descriptor_ascii_arg_info)
	PHP_FE(usb_get_descriptor  , usb_get_descriptor_arg_info)
	PHP_FE(usb_get_string_descriptor, usb_get_string_descriptor_arg_info)
	PHP_FE(usb_get_device_list , usb_get_device_list_arg_info)
	PHP_FE(usb_get_bus_number  , usb_get_bus_number_arg_info)
	PHP_FE(usb_get_device_address, usb_get_device_address_arg_info)
	PHP_FE(usb_get_device_speed, usb_get_device_speed_arg_info)
	PHP_FE(usb_get_max_packet_size, usb_get_max_packet_size_arg_info)
	PHP_FE(usb_get_max_iso_packet_size, usb_get_max_iso_packet_size_arg_info)
	PHP_FE(usb_ref_device      , usb_ref_device_arg_info)
	PHP_FE(usb_unref_device    , usb_unref_device_arg_info)
	PHP_FE(usb_open            , usb_open_arg_info)
	PHP_FE(usb_close           , usb_close_arg_info)
	PHP_FE(usb_get_configuration, usb_get_configuration_arg_info)
	PHP_FE(usb_set_configuration, usb_set_configuration_arg_info)
	PHP_FE(usb_claim_interface , usb_claim_interface_arg_info)
	PHP_FE(usb_release_interface, usb_release_interface_arg_info)
	PHP_FE(usb_set_interface_alt_setting, usb_set_interface_alt_setting_arg_info)
	PHP_FE(usb_clear_halt      , usb_clear_halt_arg_info)
	PHP_FE(usb_reset_device    , usb_reset_device_arg_info)
	PHP_FE(usb_kernel_driver_active, usb_kernel_driver_active_arg_info)
	PHP_FE(usb_detach_kernel_driver, usb_detach_kernel_driver_arg_info)
	PHP_FE(usb_attach_kernel_driver, usb_attach_kernel_driver_arg_info)
        PHP_FE(usb_control_transfer, usb_control_transfer_arg_info)
        PHP_FE(usb_bulk_transfer   , usb_bulk_transfer_arg_info)
        PHP_FE(usb_interrupt_transfer, usb_interrupt_transfer_arg_info)
        PHP_FE(usb_set_debug       , usb_set_debug_arg_info)
        PHP_FE(usb_error_name      , usb_error_name_arg_info)
	{ NULL, NULL, NULL }
};
/* }}} */


/* {{{ usb_module_entry
 */
zend_module_entry usb_module_entry = {
	STANDARD_MODULE_HEADER,
	"usb",
	usb_functions,
	PHP_MINIT(usb),     /* Replace with NULL if there is nothing to do at php startup   */ 
	PHP_MSHUTDOWN(usb), /* Replace with NULL if there is nothing to do at php shutdown  */
	PHP_RINIT(usb),     /* Replace with NULL if there is nothing to do at request start */
	PHP_RSHUTDOWN(usb), /* Replace with NULL if there is nothing to do at request end   */
	PHP_MINFO(usb),
	PHP_USB_VERSION, 
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_USB
ZEND_GET_MODULE(usb)
#endif


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(usb)
{
        REGISTER_LONG_CONSTANT("USB_SPEED_UNKNOWN", LIBUSB_SPEED_UNKNOWN, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_SPEED_LOW", LIBUSB_SPEED_LOW, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_SPEED_FULL", LIBUSB_SPEED_FULL, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_SPEED_HIGH", LIBUSB_SPEED_HIGH, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_SPEED_SUPER", LIBUSB_SPEED_SUPER, CONST_PERSISTENT | CONST_CS);
        
        REGISTER_LONG_CONSTANT("USB_CLASS_PER_INTERFACE", LIBUSB_CLASS_PER_INTERFACE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_AUDIO", LIBUSB_CLASS_AUDIO, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_COMM", LIBUSB_CLASS_COMM, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_HID", LIBUSB_CLASS_HID, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_PHYSICAL", LIBUSB_CLASS_PHYSICAL, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_PRINTER", LIBUSB_CLASS_PRINTER, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_PTP", LIBUSB_CLASS_PTP, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_IMAGE", LIBUSB_CLASS_IMAGE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_MASS_STORAGE", LIBUSB_CLASS_MASS_STORAGE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_HUB", LIBUSB_CLASS_HUB, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_DATA", LIBUSB_CLASS_DATA, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_SMART_CARD", LIBUSB_CLASS_SMART_CARD, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_CONTENT_SECURITY", LIBUSB_CLASS_CONTENT_SECURITY, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_VIDEO", LIBUSB_CLASS_VIDEO, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_PERSONAL_HEALTHCARE", LIBUSB_CLASS_PERSONAL_HEALTHCARE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_DIAGNOSTIC_DEVICE", LIBUSB_CLASS_DIAGNOSTIC_DEVICE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_WIRELESS", LIBUSB_CLASS_WIRELESS, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_APPLICATION", LIBUSB_CLASS_APPLICATION, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_VENDOR_SPEC", LIBUSB_CLASS_VENDOR_SPEC, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_CLASS_MISC", 0xEF, CONST_PERSISTENT | CONST_CS);

        REGISTER_LONG_CONSTANT("USB_DT_DEVICE", LIBUSB_DT_DEVICE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_CONFIG", LIBUSB_DT_CONFIG, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_STRING", LIBUSB_DT_STRING, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_INTERFACE", LIBUSB_DT_INTERFACE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_ENDPOINT", LIBUSB_DT_ENDPOINT, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_HID", LIBUSB_DT_HID, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_REPORT", LIBUSB_DT_REPORT, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_PHYSICAL", LIBUSB_DT_PHYSICAL, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_HUB", LIBUSB_DT_HUB, CONST_PERSISTENT | CONST_CS);

        REGISTER_LONG_CONSTANT("USB_TRANSFER_TYPE_CONTROL", LIBUSB_TRANSFER_TYPE_CONTROL, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_TRANSFER_TYPE_ISOCHRONOUS", LIBUSB_TRANSFER_TYPE_ISOCHRONOUS, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_TRANSFER_TYPE_BULK", LIBUSB_TRANSFER_TYPE_BULK, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_TRANSFER_TYPE_INTERRUPT", LIBUSB_TRANSFER_TYPE_INTERRUPT, CONST_PERSISTENT | CONST_CS);
        
        REGISTER_LONG_CONSTANT("USB_ISO_SYNC_TYPE_NONE", LIBUSB_ISO_SYNC_TYPE_NONE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ISO_SYNC_TYPE_ASYNC", LIBUSB_ISO_SYNC_TYPE_ASYNC, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ISO_SYNC_TYPE_ADAPTIVE", LIBUSB_ISO_SYNC_TYPE_ADAPTIVE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ISO_SYNC_TYPE_SYNC", LIBUSB_ISO_SYNC_TYPE_SYNC, CONST_PERSISTENT | CONST_CS);
        
        REGISTER_LONG_CONSTANT("USB_ISO_USAGE_TYPE_DATA", LIBUSB_ISO_USAGE_TYPE_DATA, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ISO_USAGE_TYPE_FEEDBACK", LIBUSB_ISO_USAGE_TYPE_FEEDBACK, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ISO_USAGE_TYPE_IMPLICIT", LIBUSB_ISO_USAGE_TYPE_IMPLICIT, CONST_PERSISTENT | CONST_CS);

        REGISTER_LONG_CONSTANT("USB_ENDPOINT_IN", LIBUSB_ENDPOINT_IN, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ENDPOINT_OUT", LIBUSB_ENDPOINT_OUT, CONST_PERSISTENT | CONST_CS);
        
        REGISTER_LONG_CONSTANT("USB_REQUEST_TYPE_STANDARD", LIBUSB_REQUEST_TYPE_STANDARD, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_TYPE_CLASS", LIBUSB_REQUEST_TYPE_CLASS, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_TYPE_VENDOR", LIBUSB_REQUEST_TYPE_VENDOR, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_TYPE_RESERVED", LIBUSB_REQUEST_TYPE_RESERVED, CONST_PERSISTENT | CONST_CS);
        
        REGISTER_LONG_CONSTANT("USB_RECIPIENT_DEVICE", LIBUSB_RECIPIENT_DEVICE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_RECIPIENT_INTERFACE", LIBUSB_RECIPIENT_INTERFACE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_RECIPIENT_ENDPOINT", LIBUSB_RECIPIENT_ENDPOINT, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_RECIPIENT_OTHER", LIBUSB_RECIPIENT_OTHER, CONST_PERSISTENT | CONST_CS);

        REGISTER_LONG_CONSTANT("USB_ENDPOINT_DIR_MASK", LIBUSB_ENDPOINT_DIR_MASK, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ENDPOINT_ADDRESS_MASK", LIBUSB_ENDPOINT_ADDRESS_MASK, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ISO_SYNC_TYPE_MASK", LIBUSB_ISO_SYNC_TYPE_MASK, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ISO_USAGE_TYPE_MASK", LIBUSB_ISO_USAGE_TYPE_MASK, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_TRANSFER_TYPE_MASK", LIBUSB_TRANSFER_TYPE_MASK, CONST_PERSISTENT | CONST_CS);

        REGISTER_LONG_CONSTANT("USB_REQUEST_GET_STATUS", LIBUSB_REQUEST_GET_STATUS, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_CLEAR_FEATURE", LIBUSB_REQUEST_CLEAR_FEATURE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_SET_FEATURE", LIBUSB_REQUEST_SET_FEATURE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_SET_ADDRESS", LIBUSB_REQUEST_SET_ADDRESS, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_GET_DESCRIPTOR", LIBUSB_REQUEST_GET_DESCRIPTOR, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_SET_DESCRIPTOR", LIBUSB_REQUEST_SET_DESCRIPTOR, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_GET_CONFIGURATION", LIBUSB_REQUEST_GET_CONFIGURATION, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_SET_CONFIGURATION", LIBUSB_REQUEST_SET_CONFIGURATION, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_GET_INTERFACE", LIBUSB_REQUEST_GET_INTERFACE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_SET_INTERFACE", LIBUSB_REQUEST_SET_INTERFACE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_REQUEST_SYNCH_FRAME", LIBUSB_REQUEST_SYNCH_FRAME, CONST_PERSISTENT | CONST_CS);

        REGISTER_LONG_CONSTANT("USB_DT_DEVICE_SIZE", LIBUSB_DT_DEVICE_SIZE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_CONFIG_SIZE", LIBUSB_DT_CONFIG_SIZE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_INTERFACE_SIZE", LIBUSB_DT_INTERFACE_SIZE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_ENDPOINT_SIZE", LIBUSB_DT_ENDPOINT_SIZE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_ENDPOINT_AUDIO_SIZE", LIBUSB_DT_ENDPOINT_AUDIO_SIZE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_DT_HUB_NONVAR_SIZE", LIBUSB_DT_HUB_NONVAR_SIZE, CONST_PERSISTENT | CONST_CS);

        REGISTER_LONG_CONSTANT("USB_SUCCESS", LIBUSB_SUCCESS, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_IO", LIBUSB_ERROR_IO, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_INVALID_PARAM", LIBUSB_ERROR_INVALID_PARAM, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_ACCESS", LIBUSB_ERROR_ACCESS, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_NO_DEVICE", LIBUSB_ERROR_NO_DEVICE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_NOT_FOUND", LIBUSB_ERROR_NOT_FOUND, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_BUSY", LIBUSB_ERROR_BUSY, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_TIMEOUT", LIBUSB_ERROR_TIMEOUT, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_OVERFLOW", LIBUSB_ERROR_OVERFLOW, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_PIPE", LIBUSB_ERROR_PIPE, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_INTERRUPTED", LIBUSB_ERROR_INTERRUPTED, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_NO_MEM", LIBUSB_ERROR_NO_MEM, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_NOT_SUPPORTED", LIBUSB_ERROR_NOT_SUPPORTED, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_ERROR_OTHER", LIBUSB_ERROR_OTHER, CONST_PERSISTENT | CONST_CS);


	le_usb_context = zend_register_list_destructors_ex(usb_context_dtor, 
						   NULL, "usb_context", module_number);
	le_usb_device_handle = zend_register_list_destructors_ex(usb_device_handle_dtor, 
						   NULL, "usb_device_handle", module_number);
	le_usb_device = zend_register_list_destructors_ex(usb_device_dtor, 
						   NULL, "usb_device", module_number);
	le_usb_device_list = zend_register_list_destructors_ex(usb_device_list_dtor, 
						   NULL, "usb_device_list", module_number);

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(usb)
{

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(usb)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(usb)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(usb)
{
	php_printf("libusb wrapper for PHP\n");
	php_info_print_table_start();
	php_info_print_table_row(2, "Version",PHP_USB_VERSION " (alpha)");
	php_info_print_table_row(2, "Released", "2012-07-26");
	php_info_print_table_row(2, "CVS Revision", "$Id: $");
	php_info_print_table_row(2, "Authors", "Keng-ichi Ahagon 'oasynnoum@gmail.com' (lead)\n");
	php_info_print_table_end();
	/* add your stuff here */

}
/* }}} */


/* {{{ proto resource usb_context usb_init([resource usb_context context])
   */
PHP_FUNCTION(usb_init)
{
	libusb_context * return_res;
	long return_res_id = -1;
	zval * context = NULL;
	int context_id = -1;
	libusb_context * res_context;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|r", &context) == FAILURE) {
		return;
	}
        
        if (context != NULL)
	ZEND_FETCH_RESOURCE(res_context, libusb_context *, &context, context_id, "usb_context", le_usb_context);

        
        libusb_init(&res_context);
        return_res = res_context;

	ZEND_REGISTER_RESOURCE(return_value, return_res, le_usb_context);
}
/* }}} usb_init */


/* {{{ proto void usb_exit(resource usb_context context)
   */
PHP_FUNCTION(usb_exit)
{
	zval * context = NULL;
	int context_id = -1;
	libusb_context * res_context;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &context) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_context, libusb_context *, &context, context_id, "usb_context", le_usb_context);



        libusb_exit(res_context);

}
/* }}} usb_exit */


/* {{{ proto resource usb_device_handle usb_open_device_with_vid_pid(resource usb_context context, int vendor_id, int product_id)
   */
PHP_FUNCTION(usb_open_device_with_vid_pid)
{
	libusb_device_handle * return_res;
	long return_res_id = -1;
	zval * context = NULL;
	int context_id = -1;
	libusb_context * res_context;

	long vendor_id = 0;
	long product_id = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &context, &vendor_id, &product_id) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_context, libusb_context *, &context, context_id, "usb_context", le_usb_context);


        return_res = libusb_open_device_with_vid_pid(res_context, vendor_id, product_id);


	ZEND_REGISTER_RESOURCE(return_value, return_res, le_usb_device_handle);
}
/* }}} usb_open_device_with_vid_pid */


/* {{{ proto resource usb_device usb_get_device(resource usb_device_handle device_handle)
   */
PHP_FUNCTION(usb_get_device)
{
	libusb_device * return_res;
	long return_res_id = -1;
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device_handle) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);



        return_res = libusb_get_device(res_device_handle);

	ZEND_REGISTER_RESOURCE(return_value, return_res, le_usb_device);
}
/* }}} usb_get_device */


/* {{{ proto object usb_get_device_descriptor(resource usb_device device)
   */
PHP_FUNCTION(usb_get_device_descriptor)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;
        struct libusb_device_descriptor * device_descriptor = (struct libusb_device_descriptor *)ecalloc(1, sizeof(struct libusb_device_descriptor));



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);



	if (libusb_get_device_descriptor(res_device, device_descriptor) != 0) {
                php_error(E_WARNING, "failed to get device descriptor"); 
                RETURN_NULL();
        }


	object_init(return_value);
        add_property_long(return_value, "bLength", device_descriptor->bLength);
        add_property_long(return_value, "bDescriptorType", device_descriptor->bDescriptorType);
        add_property_long(return_value, "bcdUSB", device_descriptor->bcdUSB);
        add_property_long(return_value, "bDeviceClass", device_descriptor->bDeviceClass);
        add_property_long(return_value, "bDeviceSubClass", device_descriptor->bDeviceSubClass);
        add_property_long(return_value, "bDeviceProtocol", device_descriptor->bDeviceProtocol);
        add_property_long(return_value, "bMaxPacketSize0", device_descriptor->bMaxPacketSize0);
        add_property_long(return_value, "idVendor", device_descriptor->idVendor);
        add_property_long(return_value, "idProduct", device_descriptor->idProduct);
        add_property_long(return_value, "bcdDevice", device_descriptor->bcdDevice);
        add_property_long(return_value, "iManufacturer", device_descriptor->iManufacturer);
        add_property_long(return_value, "iProduct", device_descriptor->iProduct);
        add_property_long(return_value, "iSerialNumber", device_descriptor->iSerialNumber);
        add_property_long(return_value, "bNumConfigurations", device_descriptor->bNumConfigurations);
        efree(device_descriptor);
}
/* }}} usb_get_device_descriptor */

static zval * convert_endpoint_array_to_zval_array(const struct libusb_endpoint_descriptor *endpoint, uint8_t  bNumEndpoints) {

    zval *wrapper_libusb_endpoint_descriptor_array;
    ALLOC_INIT_ZVAL(wrapper_libusb_endpoint_descriptor_array);
    array_init(wrapper_libusb_endpoint_descriptor_array);
    int j;
    for (j = 0; j < bNumEndpoints; j++) {
        struct libusb_endpoint_descriptor endpoint_descriptor = endpoint[j];
        zval *wrapper_libusb_endpoint_descriptor_array_elem;
        ALLOC_INIT_ZVAL(wrapper_libusb_endpoint_descriptor_array_elem);
        object_init(wrapper_libusb_endpoint_descriptor_array_elem);
        add_property_long(
                wrapper_libusb_endpoint_descriptor_array_elem, 
                "bLength", 
                endpoint_descriptor.bLength);
        add_property_long(
                wrapper_libusb_endpoint_descriptor_array_elem, 
                "bDescriptorType", 
                endpoint_descriptor.bDescriptorType);
        add_property_long(
                wrapper_libusb_endpoint_descriptor_array_elem, 
                "bEndpointAddress", 
                endpoint_descriptor.bEndpointAddress);
        add_property_long(
                wrapper_libusb_endpoint_descriptor_array_elem, 
                "bmAttributes", 
                endpoint_descriptor.bmAttributes);
        add_property_long(
                wrapper_libusb_endpoint_descriptor_array_elem, 
                "wMaxPacketSize", 
                endpoint_descriptor.wMaxPacketSize);
        add_property_long(
                wrapper_libusb_endpoint_descriptor_array_elem, 
                "bInterval", 
                endpoint_descriptor.bInterval);
        add_property_long(
                wrapper_libusb_endpoint_descriptor_array_elem, 
                "bRefresh", 
                endpoint_descriptor.bRefresh);
        add_property_long(
                wrapper_libusb_endpoint_descriptor_array_elem, 
                "bSynchAddress", 
                endpoint_descriptor.bSynchAddress);
        add_property_stringl(
                wrapper_libusb_endpoint_descriptor_array_elem, 
                "extra", 
                endpoint_descriptor.extra,
                endpoint_descriptor.extra_length, 1);
        add_property_long(
                wrapper_libusb_endpoint_descriptor_array_elem, 
                "extra_length", 
                endpoint_descriptor.extra_length);

        add_next_index_zval(wrapper_libusb_endpoint_descriptor_array, wrapper_libusb_endpoint_descriptor_array_elem);
    }
    
    return wrapper_libusb_endpoint_descriptor_array;
}

static zval * convert_altsetting_array_to_zval_array(const struct libusb_interface_descriptor *altsetting, int num_altsetting) {
    
    zval *wrapper_libusb_interface_descriptor_array;
    ALLOC_INIT_ZVAL(wrapper_libusb_interface_descriptor_array);
    array_init(wrapper_libusb_interface_descriptor_array);
    int i;
    for (i = 0; i < num_altsetting; i++) {
        zval *wrapper_libusb_interface_descriptor_array_elem;
        ALLOC_INIT_ZVAL(wrapper_libusb_interface_descriptor_array_elem);
        object_init(wrapper_libusb_interface_descriptor_array_elem);

        struct libusb_interface_descriptor interface_descriptor = altsetting[i];

        add_property_long(
                wrapper_libusb_interface_descriptor_array_elem, 
                "bLength", 
                interface_descriptor.bLength);
        add_property_long(
                wrapper_libusb_interface_descriptor_array_elem, 
                "bDescriptorType", 
                interface_descriptor.bDescriptorType);
        add_property_long(
                wrapper_libusb_interface_descriptor_array_elem, 
                "bInterfaceNumber", 
                interface_descriptor.bInterfaceNumber);
        add_property_long(
                wrapper_libusb_interface_descriptor_array_elem, 
                "bAlternateSetting", 
                interface_descriptor.bAlternateSetting);
        add_property_long(
                wrapper_libusb_interface_descriptor_array_elem, 
                "bNumEndpoints", 
                interface_descriptor.bNumEndpoints);
        add_property_long(
                wrapper_libusb_interface_descriptor_array_elem, 
                "bInterfaceClass", 
                interface_descriptor.bInterfaceClass);
        add_property_long(
                wrapper_libusb_interface_descriptor_array_elem, 
                "bInterfaceSubClass", 
                interface_descriptor.bInterfaceSubClass);
        add_property_long(
                wrapper_libusb_interface_descriptor_array_elem, 
                "bInterfaceProtocol", 
                interface_descriptor.bInterfaceProtocol);
        add_property_long(
                wrapper_libusb_interface_descriptor_array_elem, 
                "iInterface", 
                interface_descriptor.iInterface);
        add_property_zval(
                wrapper_libusb_interface_descriptor_array_elem, 
                "endpoint", 
                convert_endpoint_array_to_zval_array(interface_descriptor.endpoint, interface_descriptor.bNumEndpoints));
        add_property_stringl(
                wrapper_libusb_interface_descriptor_array_elem, 
                "extra", 
                interface_descriptor.extra,
                interface_descriptor.extra_length, 1);
        add_property_long(
                wrapper_libusb_interface_descriptor_array_elem, 
                "extra_length", 
                interface_descriptor.extra_length);

        add_next_index_zval(wrapper_libusb_interface_descriptor_array, wrapper_libusb_interface_descriptor_array_elem);
    }
    return wrapper_libusb_interface_descriptor_array;
}

static zval * convert_config_descriptor_to_zval_object(struct libusb_config_descriptor * config, zval *return_value) {
    zval *wrapper_libusb_interface;
    ALLOC_INIT_ZVAL(wrapper_libusb_interface);
    object_init(wrapper_libusb_interface);
    add_property_long(wrapper_libusb_interface, "num_altsetting", config->interface->num_altsetting);
    add_property_zval(wrapper_libusb_interface, "altsetting", convert_altsetting_array_to_zval_array(config->interface->altsetting, config->interface->num_altsetting));

    object_init(return_value);
    add_property_long(return_value, "bLength", config->bLength);
    add_property_long(return_value, "bDescriptorType", config->bDescriptorType);
    add_property_long(return_value, "wTotalLength", config->wTotalLength);
    add_property_long(return_value, "bNumInterface", config->bNumInterfaces);
    add_property_long(return_value, "bConfigurationValue", config->bConfigurationValue);
    add_property_long(return_value, "iConfiguration", config->iConfiguration);
    add_property_long(return_value, "bmAttributes", config->bmAttributes);
    add_property_long(return_value, "MaxPower", config->MaxPower);
    add_property_zval(return_value, "interface", wrapper_libusb_interface);
    add_property_stringl(return_value, "extra", config->extra, config->extra_length, 1);
    add_property_long(return_value, "extra_length", config->extra_length);

    return return_value;
}

/* {{{ proto object usb_get_config_descriptor(resource usb_device device, int config_index)
   */
PHP_FUNCTION(usb_get_config_descriptor)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;

	long config_index = 0;
        struct libusb_config_descriptor * config;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device, &config_index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

        
        if (libusb_get_config_descriptor(res_device, config_index, &config) != 0) {
            php_error(E_WARNING, "%s", "failed to get config descriptor"); 
            RETURN_NULL();
        }
        
        convert_config_descriptor_to_zval_object(config, return_value);
        
        libusb_free_config_descriptor(config);
}
/* }}} usb_get_config_descriptor */


/* {{{ proto object usb_get_active_config_descriptor(resource usb_device device)
   */
PHP_FUNCTION(usb_get_active_config_descriptor)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;
        
        struct libusb_config_descriptor * config;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);


        if (libusb_get_active_config_descriptor(res_device, &config) != 0) {
            php_error(E_WARNING, "%s", "failed to get active config descriptor"); 
            RETURN_NULL();
        }

        convert_config_descriptor_to_zval_object(config, return_value);
        
        libusb_free_config_descriptor(config);
}
/* }}} usb_get_active_config_descriptor */


/* {{{ proto object usb_get_config_descriptor_by_value(resource usb_device device, int configuration_value)
   */
PHP_FUNCTION(usb_get_config_descriptor_by_value)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;

	long configuration_value = 0;
        struct libusb_config_descriptor * config;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device, &configuration_value) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);


        if (libusb_get_config_descriptor_by_value(res_device, configuration_value, &config) != 0) {
            php_error(E_WARNING, "%s", "failed to get config descriptor by configuration value");
            RETURN_NULL();
        }
	

        convert_config_descriptor_to_zval_object(config, return_value);
        
        libusb_free_config_descriptor(config);
}
/* }}} usb_get_config_descriptor_by_value */


/* {{{ proto string usb_get_string_descriptor_ascii(resource usb_device device, int desc_index)
   */
PHP_FUNCTION(usb_get_string_descriptor_ascii)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
        libusb_device_handle * res_device_handle;

	long desc_index = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &desc_index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device", le_usb_device_handle);

        int data_size = 256;
        char *data = (char *)ecalloc(1, data_size);
        int result = libusb_get_string_descriptor_ascii(res_device_handle, desc_index, data, data_size);
        if (result < 0) {
            php_error(E_WARNING, "%s", "failed to get string descriptor ascii");
            RETURN_NULL();
        }

        char * string_descriptor = estrndup(data, result);
        efree(data);

	RETURN_STRINGL(string_descriptor, result, 0);
}
/* }}} usb_get_string_descriptor_ascii */


/* {{{ proto string usb_get_descriptor(resource usb_device_handle device_handle, int desc_type, int desc_index)
   */
PHP_FUNCTION(usb_get_descriptor)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long desc_type = 0;
	long desc_index = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &device_handle, &desc_type, &desc_index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        int data_size = 256;
        char *data = (char *)ecalloc(1, data_size);
        int result = libusb_get_descriptor(res_device_handle, desc_type, desc_index, data, data_size);
        if (result < 0) {
            php_error(E_WARNING, "%s", "failed to get descriptor");
            RETURN_NULL();
        }
	
        char * descriptor = estrndup(data, result);
        efree(data);

	RETURN_STRINGL(descriptor, result, 0);
}
/* }}} usb_get_descriptor */


/* {{{ proto string usb_get_string_descriptor(resource usb_device_handle device_handle, int desc_index, int langid)
   */
PHP_FUNCTION(usb_get_string_descriptor)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long desc_index = 0;
	long langid = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &device_handle, &desc_index, &langid) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);



        int data_size = 256;
        char *data = (char *)ecalloc(1, data_size);
        int result = libusb_get_string_descriptor(res_device_handle, desc_index, langid, data, data_size);
        if (result < 0) {
            php_error(E_WARNING, "%s", "failed to get descriptor");
            RETURN_NULL();
        }
	
        char * string_descriptor = estrndup(data, result);
        efree(data);

	RETURN_STRINGL(string_descriptor, result, 0);
}
/* }}} usb_get_string_descriptor */


/* {{{ proto array usb_get_device_list(resource usb_context context)
   */
PHP_FUNCTION(usb_get_device_list)
{	libusb_device ** device_list;
	long return_res_id = -1;
	zval * context = NULL;
	int context_id = -1;
	libusb_context * res_context;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &context) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_context, libusb_context *, &context, context_id, "usb_context", le_usb_context);



	array_init(return_value);
        
        zval *device_list_zval;
        ALLOC_INIT_ZVAL(device_list_zval);
        
        ssize_t device_list_length = libusb_get_device_list(res_context, &device_list) - 1;
        ZEND_REGISTER_RESOURCE(device_list_zval, device_list, le_usb_device_list);
        if (device_list_length < 0) {
            php_error(E_WARNING, "%s", "failed to get device list");
        } else {
            int i;
            for (i = 0; i < device_list_length; i++) {
                libusb_device *device = device_list[i];
                zval *device_zval;
                ALLOC_INIT_ZVAL(device_zval);
                ZEND_REGISTER_RESOURCE(device_zval, device, le_usb_device);
                add_next_index_zval(return_value, device_zval);
            }
        }

	
        //libusb_free_device_list(device_list, 1);

}
/* }}} usb_get_device_list */


/* {{{ proto int usb_get_bus_number(resource usb_device device)
   */
PHP_FUNCTION(usb_get_bus_number)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);


        uint8_t num = libusb_get_bus_number(res_device);

	RETURN_LONG(num);
}
/* }}} usb_get_bus_number */


/* {{{ proto int usb_get_device_address(resource usb_device device)
   */
PHP_FUNCTION(usb_get_device_address)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);


        uint8_t address = libusb_get_device_address(res_device);
        
	RETURN_LONG(address);
}
/* }}} usb_get_device_address */


/* {{{ proto int usb_get_device_speed(resource usb_device device)
   */
PHP_FUNCTION(usb_get_device_speed)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);


        int speed_code = libusb_get_device_speed(res_device);

	RETURN_LONG(speed_code);
}
/* }}} usb_get_device_speed */


/* {{{ proto int usb_get_max_packet_size(resource usb_device device, int endpoint)
   */
PHP_FUNCTION(usb_get_max_packet_size)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;

	long endpoint = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device, &endpoint) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);


        int max_packet_size = libusb_get_max_packet_size(res_device, endpoint);
        if (max_packet_size < 0) {
            char *msg;
            switch (max_packet_size) {
                case LIBUSB_ERROR_NOT_FOUND:
                    msg = "failed to get max packet size. specified endpoint does not exist.";
                    break;
                default:
                case LIBUSB_ERROR_OTHER:
                    msg = "failed to get max packet size.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
        }

	RETURN_LONG(max_packet_size);
}
/* }}} usb_get_max_packet_size */


/* {{{ proto int usb_get_max_iso_packet_size(resource usb_device device, int endpoint)
   */
PHP_FUNCTION(usb_get_max_iso_packet_size)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;

	long endpoint = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device, &endpoint) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);



        int max_packet_size = libusb_get_max_iso_packet_size(res_device, endpoint);
        if (max_packet_size < 0) {
            char *msg;
            switch (max_packet_size) {
                case LIBUSB_ERROR_NOT_FOUND:
                    msg = "failed to get max iso packet size. specified endpoint does not exist.";
                    break;
                default:
                case LIBUSB_ERROR_OTHER:
                    msg = "failed to get max iso packet size.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
        }

	RETURN_LONG(max_packet_size);
}
/* }}} usb_get_max_iso_packet_size */


/* {{{ proto resource usb_device usb_ref_device(resource usb_device device)
   */
PHP_FUNCTION(usb_ref_device)
{
	libusb_device * return_res;
	long return_res_id = -1;
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);



        return_res = libusb_ref_device(res_device);

	ZEND_REGISTER_RESOURCE(return_value, return_res, le_usb_device);
}
/* }}} usb_ref_device */


/* {{{ proto void usb_unref_device(resource usb_device device)
   */
PHP_FUNCTION(usb_unref_device)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);



        libusb_unref_device(res_device);

}
/* }}} usb_unref_device */


/* {{{ proto resource usb_device_handle usb_open(resource usb_device device)
   */
PHP_FUNCTION(usb_open)
{
	libusb_device_handle * return_res;
	long return_res_id = -1;
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);


        int result = libusb_open(res_device, &return_res);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_NO_MEM:
                    msg = "failed to open device. failed to allocate memory.";
                    break;
                case LIBUSB_ERROR_ACCESS:
                    msg = "failed to open device. permission denied.";
                    break;
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to open device. specified device does not exist.";
                    break;
                default:
                    msg = "failed to open device.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
            RETURN_NULL();
        }

	ZEND_REGISTER_RESOURCE(return_value, return_res, le_usb_device_handle);
}
/* }}} usb_open */


/* {{{ proto void usb_close(resource usb_device_handle device_handle)
   */
PHP_FUNCTION(usb_close)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device_handle) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        libusb_close(res_device_handle);

}
/* }}} usb_close */


/* {{{ proto int usb_get_configuration(resource usb_device_handle device_handle)
   */
PHP_FUNCTION(usb_get_configuration)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device_handle) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        int config = 0;
        int result = libusb_get_configuration(res_device_handle, &config);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to get configuration. specified device does not exist.";
                    break;
                default:
                    msg ="failed to get configuration.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
            RETURN_LONG(result);
        }

	RETURN_LONG(config);
}
/* }}} usb_get_configuration */


/* {{{ proto int usb_set_configuration(resource usb_device_handle device_handle, int configuration)
   */
PHP_FUNCTION(usb_set_configuration)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long configuration = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &configuration) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        int result = libusb_set_configuration(res_device_handle, configuration);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_NOT_FOUND:
                    msg = "failed to set configuration. the requested configuration does not exist";
                    break;
                case LIBUSB_ERROR_BUSY:
                    msg = "failed to set configuration. interfaces are currently claimed";
                    break;
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to set configuration. device has been disconnected";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
        }

	RETURN_LONG(result);
}
/* }}} usb_set_configuration */


/* {{{ proto int usb_claim_interface(resource usb_device_handle device_handle, int interface_number)
   */
PHP_FUNCTION(usb_claim_interface)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &interface_number) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        int result = libusb_claim_interface(res_device_handle, interface_number);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_NOT_FOUND:
                    msg = "failed to claim interface. the requested interface does not exist.";
                    break;
                case LIBUSB_ERROR_BUSY:
                    msg = "failed to claim interface. another program or driver has claimed the interface.";
                    break;
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to claim interface. the device has been disconnected.";
                    break;
                default:
                    msg = "failed to claim interface.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
        }

	RETURN_LONG(result);
}
/* }}} usb_claim_interface */


/* {{{ proto int usb_release_interface(resource usb_device_handle device_handle, int interface_number)
   */
PHP_FUNCTION(usb_release_interface)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &interface_number) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        int result = libusb_release_interface(res_device_handle, interface_number);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_NOT_FOUND:
                    msg = "failed to release interface. the interface was not claimed.";
                    break;
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to release interface. the device has been disconnected.";
                    break;
                default:
                    msg = "failed to release interface.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
        }
	

	RETURN_LONG(result);
}
/* }}} usb_release_interface */


/* {{{ proto int usb_set_interface_alt_setting(resource usb_device_handle device_handle, int interface_number, int alternate_setting)
   */
PHP_FUNCTION(usb_set_interface_alt_setting)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;
	long alternate_setting = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &device_handle, &interface_number, &alternate_setting) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        int result = libusb_set_interface_alt_setting(res_device_handle, interface_number, alternate_setting);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_NOT_FOUND:
                    msg = "failed to set interface alternate setting. the interface was not claimed, or the requested alternate setting does not exist.";
                    break;
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to set interface alternate setting. the device has been disconnected.";
                    break;
                default:
                    msg = "failed to set interface alternate setting.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
        }
	

	RETURN_LONG(result);
}
/* }}} usb_set_interface_alt_setting */


/* {{{ proto int usb_clear_halt(resource usb_device_handle device_handle, int endpoint)
   */
PHP_FUNCTION(usb_clear_halt)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long endpoint = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &endpoint) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        int result = libusb_clear_halt(res_device_handle, endpoint);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_NOT_FOUND:
                    msg = "failed to clear halt. the endpoint does not exist.";
                    break;
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to clear halt. the device has been disconnected.";
                    break;
                default:
                    msg = "failed to clear halt.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
        }
	

	RETURN_LONG(result);
}
/* }}} usb_clear_halt */


/* {{{ proto int usb_reset_device(resource usb_device_handle device_handle)
   */
PHP_FUNCTION(usb_reset_device)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device_handle) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        int result = libusb_reset_device(res_device_handle);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_NOT_FOUND:
                    msg = "failed to reset device. maybe re-enumeration is required, or the device has been disconnected.";
                    break;
                default:
                    msg = "failed to reset device.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
        }
	

	RETURN_LONG(result);
}
/* }}} usb_reset_device */


/* {{{ proto int usb_kernel_driver_active(resource usb_device_handle device_handle, int interface_number)
   */
PHP_FUNCTION(usb_kernel_driver_active)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &interface_number) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        int result = libusb_kernel_driver_active(res_device_handle, interface_number);
        if (result != 0 && result != 1) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to kernel driver active. the device has been disconnected.";
                    break;
                case LIBUSB_ERROR_NOT_SUPPORTED:
                    msg = "failed to kernel driver active. the functionality is not available on this system.";
                    break;
                default:
                    msg = "failed to kernel driver active.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
        }
	

	RETURN_LONG(result);
}
/* }}} usb_kernel_driver_active */


/* {{{ proto int usb_detach_kernel_driver(resource usb_device_handle device_handle, int interface_number)
   */
PHP_FUNCTION(usb_detach_kernel_driver)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &interface_number) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        int result = libusb_detach_kernel_driver(res_device_handle, interface_number);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_NOT_FOUND:
                    msg = "failed to detach kernel driver. no kernel driver was active.";
                    break;
                case LIBUSB_ERROR_INVALID_PARAM:
                    msg = "failed to detach kernel driver. specified interface does not exist.";
                    break;
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to detach kernel driver. the device has been disconnected.";
                    break;
                case LIBUSB_ERROR_NOT_SUPPORTED:
                    msg = "failed to detach kernel driver. the functionality is not available on this system.";
                    break;
                default:
                    msg = "failed to detach kernel driver.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
        }
	

	RETURN_LONG(result);
}
/* }}} usb_detach_kernel_driver */


/* {{{ proto int usb_attach_kernel_driver(resource usb_device_handle device_handle, int interface_number)
   */
PHP_FUNCTION(usb_attach_kernel_driver)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &interface_number) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);


        int result = libusb_attach_kernel_driver(res_device_handle, interface_number);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_NOT_FOUND:
                    msg = "failed to re-attach kernel driver. no kernel driver was active.";
                    break;
                case LIBUSB_ERROR_INVALID_PARAM:
                    msg = "failed to re-attach kernel driver. specified interface does not exist.";
                    break;
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to re-attach kernel driver. the device has been disconnected.";
                    break; 
                case LIBUSB_ERROR_NOT_SUPPORTED:
                    msg = "failed to re-attach kernel driver. the functionality is not available on this system.";
                    break;
                case LIBUSB_ERROR_BUSY:
                    msg = "failed to re-attach kernel driver because the interface is claimed by a program or driver.";
                    break;
                default:
                    msg = "failed to re-attach kernel driver.";
                    break;
            }
            
            php_error(E_WARNING, "%s", msg);
        }

	RETURN_LONG(result);
}
/* }}} usb_attach_kernel_driver */

/* {{{ proto int usb_control_transfer(resource usb_device_handle device_handle, int bmRequestType, int bRequest, int wValue, int wIndex, array &data, int wLength[, int timeout])
   */
PHP_FUNCTION(usb_control_transfer)
{
        zval * device_handle = NULL;
        int device_handle_id = -1;
        libusb_device_handle * res_device_handle;

        long bmRequestType = 0;
        long bRequest = 0;
        long wValue = 0;
        long wIndex = 0;
        zval * data = NULL;
        HashTable * data_hash = NULL;
        HashPosition pointer;
        long wLength = 0;
        long timeout = 0;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rllllal|l", &device_handle, &bmRequestType, &bRequest, &wValue, &wIndex, &data, &wLength, &timeout) == FAILURE) {
                return;
        }
        ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);
        data_hash = HASH_OF(data);

        if (wLength < 0) {
            php_error(E_ERROR, "failed to control transfer. wLength should not be negative.");;
            RETURN_LONG(LIBUSB_ERROR_OTHER);
        }
        
        
        unsigned char *buf;
        int buf_size;
        int is_endpoint_in = bmRequestType & LIBUSB_ENDPOINT_DIR_MASK;
        
        buf_size = (uint16_t)wLength;
        buf = (unsigned char *)ecalloc(1, buf_size);
        
        if (!is_endpoint_in) {
            zval **current_data;
            int c = 0;
            for (
                zend_hash_internal_pointer_reset_ex(data_hash, &pointer);
                zend_hash_get_current_data_ex(data_hash, (void **)&current_data, &pointer) == SUCCESS;
                zend_hash_move_forward_ex(data_hash, &pointer), c++
            ) {
                //buf[c] = (unsigned char)Z_LVAL_P(current_data);
                int i = 0;
                int scale = 1;
                unsigned char *string_value;
                unsigned char ch;
                switch (Z_TYPE_PP(current_data)) {
                    case IS_BOOL:
                        buf[c] = (unsigned char)Z_BVAL_PP(current_data);
                        break;
                    case IS_LONG:
                        buf[c] = (unsigned char)Z_LVAL_PP(current_data);
                        break;
                    case IS_DOUBLE:
                        buf[c] = (unsigned char)Z_DVAL_PP(current_data);
                        break;
                    case IS_STRING:
                        string_value = Z_STRVAL_PP(current_data);
                        scale = Z_STRLEN_PP(current_data);
                        for (i = 0; i < scale; i++) {
                            buf[c++] = (unsigned char)string_value[i];
                        }
                        c--;
                        break;
                    default:
                        //buf[c] = 0;
                        php_error(E_ERROR, "failed to write via control transfer. unwritable type found in byte array index(%d). type of element must be bool, int or string.", c);
                        efree(buf);
                        RETURN_LONG(LIBUSB_ERROR_OTHER);
                        break;
                }
            }
        }
        
        int result = libusb_control_transfer(
                        res_device_handle, 
                        bmRequestType, 
                        bRequest, 
                        wValue, 
                        wIndex, 
                        buf, 
                        buf_size, 
                        timeout);
        if (result < 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_TIMEOUT:
                    msg = "failed to control transfer. the transfer timed out.";
                    break;
                case LIBUSB_ERROR_PIPE:
                    msg = "failed to control transfer. specified device does not support control transfer.";
                    break;
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to control transfer. specified device has been disconnected.";
                    break;
                default:
                    msg = "failed to control transfer.";
                    break;
            }
            php_error(E_WARNING, msg);
            efree(buf);
            RETURN_LONG(result);
        }

        if (is_endpoint_in) {
            zval_dtor(data);
            array_init(data);
            
            int c = 0;
            for (c = 0; c < buf_size; c++) {
                add_index_long(data, c, (unsigned char)buf[c]);
            }
        }
        
        efree(buf);
        
        RETURN_LONG(result);
}
/* }}} usb_control_transfer */


/* {{{ proto int usb_bulk_transfer(resource usb_device_handle device_handle, int endpoint, array &data, int length[, int timeout])
   */
PHP_FUNCTION(usb_bulk_transfer)
{
        zval * device_handle = NULL;
        int device_handle_id = -1;
        libusb_device_handle * res_device_handle;

        long endpoint = 0;
        zval * data = NULL;
        HashTable * data_hash = NULL;
        HashPosition pointer;
        long length = 0;
        long timeout = 0;



        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlal|l", &device_handle, &endpoint, &data, &length, &timeout) == FAILURE) {
                return;
        }
        ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);
        data_hash = HASH_OF(data);


        if (length < 0) {
            php_error(E_ERROR, "failed to bulk transfer. length should not be negative.");
            RETURN_LONG(LIBUSB_ERROR_OTHER);
        }

        unsigned char *buf;
        int buf_size;
        int transferred = 0;
        int is_endpoint_in = LIBUSB_ENDPOINT_DIR_MASK & endpoint;
        
        buf_size = length;
        buf = (unsigned char *)ecalloc(1, buf_size);
        
        if (!is_endpoint_in) {
            zval **current_data;
            int c = 0;
            for (
                zend_hash_internal_pointer_reset_ex(data_hash, &pointer);
                (zend_hash_get_current_data_ex(data_hash, (void **)&current_data, &pointer) == SUCCESS);
                zend_hash_move_forward_ex(data_hash, &pointer), c++
            ) {
                //buf[c] = (unsigned char)Z_LVAL_P(current_data);
                int i = 0;
                int scale = 1;
                unsigned char *string_value;
                unsigned char ch;
                switch (Z_TYPE_PP(current_data)) {
                    case IS_BOOL:
                        buf[c] = (unsigned char)Z_BVAL_PP(current_data);
                        break;
                    case IS_LONG:
                        buf[c] = (unsigned char)Z_LVAL_PP(current_data);
                        break;
                    case IS_DOUBLE:
                        buf[c] = (unsigned char)Z_DVAL_PP(current_data);
                        break;
                    case IS_STRING:
                        string_value = Z_STRVAL_PP(current_data);
                        scale = Z_STRLEN_PP(current_data);
                        for (i = 0; i < scale; i++) {
                            buf[c++] = (unsigned char)string_value[i];
                        }
                        c--;
                        break;
                    default:
                        //buf[c] = 0;
                        php_error(E_ERROR, "failed to write via bulk transfer. unwritable type found in byte array index(%d). type of element must be bool, int or string.", c);
                        efree(buf);
                        RETURN_LONG(LIBUSB_ERROR_OTHER);
                        break;
                }
            }
        }
        
        int result = libusb_bulk_transfer(res_device_handle, endpoint, buf, buf_size, &transferred, timeout);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_TIMEOUT:
                    msg = "failed to bulk transfer. the transfer timed out.";
                    break;
                case LIBUSB_ERROR_PIPE:
                    msg = "failed to bulk transfer. the endpoint halted.";
                    break;
                case LIBUSB_ERROR_OVERFLOW:
                    msg = "failed to bulk transfer. packet overflow. the device offered more data.";
                    break;
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to bulk transfer.specified device has been connected.";
                    break;
                default:
                    msg = "failed to bulk transfer.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
            efree(buf);
            RETURN_LONG(result);
        }
        
        if (is_endpoint_in) {
            zval_dtor(data);
            array_init(data);
            
            int c = 0;
            for (c = 0; c < buf_size; c++) {
                add_index_long(data, c, (unsigned char)buf[c]);
            }
        }
        
        efree(buf);
        RETURN_LONG(transferred);
}
/* }}} usb_bulk_transfer */


/* {{{ proto int usb_interrupt_transfer(resource usb_device_handle device_handle, int endpoint, array &data, int length[, int timeout])
   */
PHP_FUNCTION(usb_interrupt_transfer)
{
        zval * device_handle = NULL;
        int device_handle_id = -1;
        libusb_device_handle * res_device_handle;

        long endpoint = 0;
        zval * data = NULL;
        HashTable * data_hash = NULL;
        HashPosition pointer;
        long length = 0;
        long timeout = 0;


        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlal|l", &device_handle, &endpoint, &data, &length, &timeout) == FAILURE) {
                return;
        }
        ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);
        data_hash = HASH_OF(data);

        
        if (length < 0) {
            php_error(E_ERROR, "failed to intterupt transfer. length should not be negative.");
            RETURN_LONG(LIBUSB_ERROR_OTHER);
        }

        unsigned char *buf;
        int buf_size;
        int transferred = 0;
        int is_endpoint_in = LIBUSB_ENDPOINT_DIR_MASK & endpoint;
        
        buf_size = length;
        buf = (unsigned char *)ecalloc(1, buf_size);
        
        if (!is_endpoint_in) {
            zval **current_data;
            int c = 0;
            for (
                zend_hash_internal_pointer_reset_ex(data_hash, &pointer);
                zend_hash_get_current_data_ex(data_hash, (void **)&current_data, &pointer) == SUCCESS;
                zend_hash_move_forward_ex(data_hash, &pointer), c++
            ) {
                //buf[c] = (unsigned char)Z_LVAL_P(current_data);
                int i = 0;
                int scale = 1;
                unsigned char *string_value;
                unsigned char ch;
                switch (Z_TYPE_PP(current_data)) {
                    case IS_BOOL:
                        buf[c] = (unsigned char)Z_BVAL_PP(current_data);
                        break;
                    case IS_LONG:
                        buf[c] = (unsigned char)Z_LVAL_PP(current_data);
                        break;
                    case IS_DOUBLE:
                        buf[c] = (unsigned char)Z_DVAL_PP(current_data);
                        break;
                    case IS_STRING:
                        string_value = Z_STRVAL_PP(current_data);
                        scale = Z_STRLEN_PP(current_data);
                        for (i = 0; i < scale; i++) {
                            buf[c++] = (unsigned char)string_value[i];
                        }
                        c--;
                        break;
                    default:
                        //buf[c] = 0;
                        php_error(E_ERROR, "failed to write via interrupt transfer. unwritable type found in byte array index(%d). type of element must be bool, int or string.", c);
                        efree(buf);
                        RETURN_LONG(LIBUSB_ERROR_OTHER);
                        break;
                }
            }
        }
        
        int result = libusb_interrupt_transfer(res_device_handle, endpoint, buf, buf_size, &transferred, timeout);
        if (result != 0) {
            char *msg;
            switch (result) {
                case LIBUSB_ERROR_TIMEOUT:
                    msg = "failed to interrupt transfer. the transfer timed out.";
                    break;
                case LIBUSB_ERROR_PIPE:
                    msg = "failed to interrupt transfer. the endpoint halted.";
                    break;
                case LIBUSB_ERROR_OVERFLOW:
                    msg = "failed to interrupt transfer. packet overflow. the device offered more data.";
                    break;
                case LIBUSB_ERROR_NO_DEVICE:
                    msg = "failed to interrupt transfer.specified device has been connected.";
                    break;
                default:
                    msg = "failed to interrupt transfer.";
                    break;
            }
            php_error(E_WARNING, "%s", msg);
            efree(buf);
            RETURN_LONG(result);
        }
        
        
        if (is_endpoint_in) {
            zval_dtor(data);
            array_init(data);
            
            int c = 0;
            for (c = 0; c < buf_size; c++) {
                add_index_long(data, c, (unsigned char)buf[c]);
            }
        }
        
        efree(buf);
        RETURN_LONG(transferred);
}
/* }}} usb_interrupt_transfer */

/* {{{ proto void usb_set_debug(resource usb_context context, int level)
   */
PHP_FUNCTION(usb_set_debug)
{
        zval * context = NULL;
        int context_id = -1;
        libusb_context * res_context;

        long level = 0;



        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &context, &level) == FAILURE) {
                return;
        }
        ZEND_FETCH_RESOURCE(res_context, libusb_context *, &context, context_id, "usb_context", le_usb_context);



        libusb_set_debug(res_context, level);

}
/* }}} usb_set_debug */

/* {{{ proto string usb_error_name(int error_code)
   */
PHP_FUNCTION(usb_error_name)
{

        long error_code = 0;



        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &error_code) == FAILURE) {
                return;
        }

        RETURN_STRING(estrdup(libusb_error_name(error_code)), 1);
}
/* }}} usb_error_name */



#endif /* HAVE_USB */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
