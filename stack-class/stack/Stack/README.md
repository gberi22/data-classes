variable-sized elements, metadata, and offset calculations:

Access to the last element requires traversing the metadata (LAST_ELEM_START, LAST_ELEM_END macros).
Each element has metadata (size and offset to the previous element) stored alongside it, which allows for flexible but complex element management.
Requires calculating offsets and managing pointers during every push and pop operation