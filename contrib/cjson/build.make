# Build static lib from object files
out/cJSON.a: out/cJSON_cjson.o
	$(call print_spc)
	@echo "$<\r[\033[1m$(TOOLPREFIX)ar\033[0m]"
	@$(TOOLPREFIX)ar rcs $@ $^

out/%_cjson.o: contrib/cjson/%.c
	$(call print_spc)
	@echo "$<\r[\033[1m$(GCC)\033[0m]"
	@$(GCC) $(CFL) $< -o$@