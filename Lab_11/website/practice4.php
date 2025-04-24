<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['size'])) {
    $size = intval($_POST['size']);
    if ($size > 0) {
        echo "<h1>Multiplication Table up to $size</h1>";
        echo "<table border='1' cellpadding='10'>";
        for ($i = 1; $i <= $size; $i++) {
            echo "<tr>";
            for ($j = 1; $j <= $size; $j++) {
                echo "<td>" . ($i * $j) . "</td>";
            }
            echo "</tr>";
        }
        
        echo "</table>";
    } else {
        echo "<p>Please enter a positive number for the table size.</p>";
    }
}
?>
