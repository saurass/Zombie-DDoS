<?php

require_once 'functions.php';

$all_bot_data = getBotsData();

$flag = 0;
foreach($all_bot_data as $bot_id => $time) {
    if($bot_id == $_GET['bot_id']) {
        $all_bot_data[$bot_id] = time();
        $flag = 1;
    }
    if((time()-$time) >= 100)
        unset($all_bot_data[$bot_id]);
}

if($flag == 0) {
    $all_bot_data[$_GET['bot_id']] = time();
}
saveBotData($all_bot_data);

echo getAttackValue();

?>