#! /bin/bash

declare -r	extension=".sh"
declare -r	filename="${0%.*}"
declare -r	settings_file="$filename"_settings"$extension"

source $settings_file

function	main()
{
	exit 0;
}

main $@
