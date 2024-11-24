#! /bin/bash

declare -r	extension=".sh";
declare -r	filename="${0%.*}";
declare -r	settings_file="$filename"_settings"$extension";

source $settings_file

function	main()
{

	exit 0;
}

function	is_function_prototype()
{
	local	exit_status=1;
	local	regex_is_function='^\w+.[[:space:]]+.*\w+\(([[:space:]]*.+)+\);';


	if [[ $(echo "$@" | grep -P $regex_is_function ) ]]; then
		exit_status=0;
	fi
	return $exit_status;
}

function	read_file()
{
	local	file_line;

	while read -r file_line; do
		if is_function_prototype "$file_line"; then
			echo "\"$file_line\" is function"
		fi
	done < "$@"
	return ;
}

#main $@;
read_file "$@";
#declare -r	file_body=$(read_file "$@");
#echo "$file_body";
#for line in "$file_body"; do
#	echo "line: $line";
#done
