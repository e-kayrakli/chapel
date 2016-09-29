module PrefetchHooks {
  extern type prefetch_entry_t;

  extern proc 
    chpl_comm_prefetch(node, raddr, size,
      serialized_base_idx): prefetch_entry_t;
  
  extern proc 
    get_prefetched_data(handle, offset, size, ref dest): c_int;

  extern proc 
    get_prefetched_data_addr(handle, offset, size, ref isPrefetched):
      c_void_ptr;

}
