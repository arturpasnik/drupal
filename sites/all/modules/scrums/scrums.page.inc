<?php

function getAuthToken()
{
	$url = 'http://scrums.local/oauth/token';
	$fields = array(

		'grant_type' => 'client_credentials',
		'client_id' => '5',
		'client_secret' => 'rWwZUcRl0CibXYFtY6B8AarYx4pzNwgQwaQlvsNR',
		'scope' => '',
	);
	$fields_string = '';
	//url-ify the data for the POST
	foreach ($fields as $key => $value) {
		$fields_string .= $key . '=' . $value . '&';
	}
	rtrim($fields_string, '&');

	$timeout = 5;
	//open connection
	$ch = curl_init();

	//set the url, number of POST vars, POST data
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($ch, CURLOPT_POST, count($fields));
	curl_setopt($ch, CURLOPT_POSTFIELDS, $fields_string);

	//execute post
	$result = curl_exec($ch);

	//close connection
	curl_close($ch);
	//dump($result);
	if ($result) {
		return getData('http://scrums.local/web_client/season/current', json_decode($result));
	} else {
		return 'Not found';
	}
}

function getData($url, $token, $array = false)
{

	//dump($token);

	$headers = [
		'Authorization: Bearer ' . $token->access_token,
		'Accept: application/json'
	];

	$ch = curl_init();
	$timeout = 5;
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);

	$data = curl_exec($ch);
	curl_close($ch);
	return $data;
}


function scrums_show_test_page($args)
{
	$response = getAuthToken();
	var_dump($args);
	if ($response) {
		$data = json_decode($response, true);
		if (is_array($data)) {
			$output = "<ul>";
			$output .= "<li>Name: ".t($data['name'])."</li>";
			$output .= "</ul>";
			drupal_set_title('Fixtures and Results '.$data['name']);
			return $output;
		}
	}
}

function scrums_title_callback($newTitle) {
	$title = $newTitle;
	return $title;
}