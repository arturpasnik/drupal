<?php

function fixtures_and_results_page($args = null)
{

	$authScrums = new AuthScrums();

	$response = $authScrums->getData('season/current');

	if ($response) {
		$data = json_decode($response, true);
		if (is_array($data)) {
			$output = "<ul>";
			$output .= "<li>Name: " . t($data['name']) . "</li>";
			$output .= "</ul>";
			drupal_set_title('Fixtures and Results ' . $data['name']);
			return $output;
		}
	}
}