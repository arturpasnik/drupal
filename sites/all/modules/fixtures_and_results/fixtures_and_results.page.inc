<?php

function fixtures_and_results_page($args = null)
{

	$authScrums = new AuthScrums();

	$response = $authScrums->getData('current-season-competitions');

	if ($response) {
		$data = json_decode($response, true);
		if (is_array($data)) {
			$output = "<h2>".t($data['name'])."</h2>";
			$output .= "<ul>";
			foreach ($data['competitions'] as $competition){
				$output .= "<li>" . t($competition['name']) . "</li>";
			}
			$output .= "</ul>";
			drupal_set_title('Fixtures and Results ' . $data['name']);
			return $output;
		}
	}
}