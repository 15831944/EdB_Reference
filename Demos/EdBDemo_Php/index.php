<!DOCTYPE html>
<html>
<body>

<?php
$EdBApi = new COM("EdBApi_COM.EdBApi");
$ret = $EdBApi ->EdB_Login("116.228.149.86", 7708, "10.11", "280079160", "830406", "", "16");
echo "登录返回值：";
echo $ret;
?>

</body>
</html>