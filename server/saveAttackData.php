<?php
require_once "functions.php";

if(isset($_POST['link']) and isset($_POST['iter'])) {
    $link = trim($_POST['link']);
    $iter = intval(trim($_POST['iter']));
    if (empty($link) || empty($iter)) {
        echo "<p>Invalid data, link or iteration are empty, or iteration is invalid</p>";
        die();
    }
    elseif (!is_int($iter)) {
        echo "<p>Invalid data, iteration isn't int</p>";
        die();
    }
    saveLinkAndIter($link, $iter);
    echo "<script>alert('attack data saved'); location.assign(\"/\")</script>";
} else {
    echo "<script>alert('some data is missing'); location.assign(\"/\")</script>";
}

header('location: index.php');

?>