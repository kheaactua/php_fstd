<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('fstd')) {
	dl('fstd.' . PHP_SHLIB_SUFFIX);
}
$module = 'fstd';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
$function = 'confirm_' . $module . '_compiled';
if (extension_loaded($module)) {
	$str = $function($module);
} else {
	$str = "Module $module is not compiled into PHP";
}
echo "$str\n";

//echo "Running:\n";
//$arr=fstd_test('>>');
//print "Result:\n";
//print_r($arr);

echo "Running:\n";
$arr=fstd_readOne('test.fst', 'o3_', 100, 1);
print "Result:\n";
print_r($arr);
