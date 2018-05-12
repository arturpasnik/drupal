<?php

function fixtures_and_results_page($args = null)
{

	$authScrums = new AuthScrums();

	$response = $authScrums->getData('current-season');

	if ($response) {
		$data = json_decode($response, true);
		if (is_array($data)) {
			$output = "<h1>Season: " . t($data['name']) . "</h1>";
			drupal_set_title('Fixtures and Results ' . $data['name']);
			return $output;
		}
	}
}