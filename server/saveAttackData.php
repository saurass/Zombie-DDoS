<?php
require_once "functions.php";

if(isset($_POST['link']) and isset($_POST['iter'])) {
    $link = $_POST['link'];
    $iter = $_POST['iter'];
    saveLinkAndIter($link, $iter);
    echo "<script>alert('attack data saved')</script>";
} else {
    echo "<script>alert('some data is missing')</script>";
}

header('location: index.php');

?>