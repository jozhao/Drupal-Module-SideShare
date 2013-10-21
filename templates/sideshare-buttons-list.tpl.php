<?php

/**
 * @file
 * Template display social sharing buttons.
 */

?>

<div id="sideshare-floating-bar">
	<div class="sideshare-box">
		<ul>
        <?php       
        foreach ( $buttons as $key => $value ) {
          echo "<li>" . _sideshare_display_button($value->button_icon, $value->button_name) . "</li>";
        }
        ?>           
    </ul>
	</div>
</div>
