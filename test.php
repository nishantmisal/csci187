
function meta_form( $post = null ) {
	global $wpdb;
	$post = get_post( $post );
	$keys = apply_filters( 'postmeta_form_keys', null, $post );

	if ( null === $keys ) {
		$limit = apply_filters( 'postmeta_form_limit', 30 );
		$keys = $wpdb->get_col(
			$wpdb->prepare(
				"SELECT DISTINCT meta_key
				FROM $wpdb->postmeta
				WHERE meta_key NOT BETWEEN '_' AND '_z'
				HAVING meta_key NOT LIKE %s
				ORDER BY meta_key
				LIMIT %d",
				$wpdb->esc_like( '_' ) . '%',
				$limit
			)
		);
	}

	if ( $keys ) {
		natcasesort( $keys );
		$meta_key_input_id = 'metakeyselect';
	} else {
		$meta_key_input_id = 'metakeyinput';
	}
?> 
<p><strong><?php _e( 'Add New Custom Field:' ); ?></strong></p>
<table id="newmeta">
<thead>
<tr>
<th class="left"><label for="<?php echo $meta_key_input_id; ?>"><?php _ex( 'Name', 'meta name' ); ?></label></th>
<th><label for="metavalue"><?php _e( 'Value' ); ?></label></th>
</tr>
</thead>

<tbody>
<tr>
<td id="newmetaleft" class="left">
	<?php if ( $keys ) { ?>
<select id="metakeyselect" name="metakeyselect">
<option value="#NONE#"><?php _e( '&mdash; Select &mdash;' ); ?></option>
		<?php
		foreach ( $keys as $key ) {
			if ( is_protected_meta( $key, 'post' ) || ! current_user_can( 'add_post_meta', $post->ID, $key ) ) {
				continue;
			}
			echo "\n<option value='" . esc_attr( $key ) . "'>" . esc_html( $key ) . '</option>';
		}
		?>
</select>
<input class="hide-if-js" type="text" id="metakeyinput" name="metakeyinput" value="" />
<a href="#postcustomstuff" class="hide-if-no-js" onclick="jQuery('#metakeyinput, #metakeyselect, #enternew, #cancelnew').toggle();return false;">
<span id="enternew"><?php _e( 'Enter new' ); ?></span>
<span id="cancelnew" class="hidden"><?php _e( 'Cancel' ); ?></span></a>
<?php } else { ?>
<input type="text" id="metakeyinput" name="metakeyinput" value="" />
<?php } ?>
</td>
<td><textarea id="metavalue" name="metavalue" rows="2" cols="25"></textarea></td>
</tr>

<tr><td colspan="2">
<div class="submit">
	<?php
	submit_button(
		__( 'Add Custom Field' ),
		'',
		'addmeta',
		false,
		array(
			'id'            => 'newmeta-submit',
			'data-wp-lists' => 'add:the-list:newmeta',
		)
	);
	?>
</div>
<?php wp_nonce_field( 'add-meta', '_ajax_nonce-add-meta', false )?>
}