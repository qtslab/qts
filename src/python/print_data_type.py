variables = locals()
variables_copy = variables.copy()
for var_name, var_value in variables_copy.items():
    print(f"{var_name}: {type(var_value)}")