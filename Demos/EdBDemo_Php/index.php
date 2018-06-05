<!DOCTYPE html>
<html>
<body>

<?php
$EdBApi = new COM("EdBApi_COM.EdBApi");
$clientID = $EdBApi->EdB_Login("116.228.149.86", 7708, "10.11", "280079160", "830406", "", "16");
echo "Login: ";
echo $clientID;
$queryData = $EdBApi->EdB_QueryData("280079160", $clientID, 2014);
echo "</br> QueryData: ";
echo $queryData;
$sendOrder = $EdBApi->EdB_SendOrder($clientID, 15, "280079160", "70000", "70000", 1, (float)1.0);
echo "</br> SendOrder: ";
echo $sendOrder;
$getPrice =  $EdBApi->EdB_GetPrice($clientID, "70000");
echo "</br> GetPrice: ";
echo $getPrice;
$cancelOrder = $EdBApi->EdB_CancelOrder($clientID, "70000", "111", 1);
echo "</br> CancelOrder: ";
echo $cancelOrder;
?>

</body>
</html>