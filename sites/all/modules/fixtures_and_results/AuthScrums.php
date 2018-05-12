<?php

class AuthScrums
{

	private $_url = 'http://scrums.local/';
	private $_clientId = 3;
	private $_clientSecret = 'A6dh4ZrNiTiiCCD41y8GTZbSlnZGALSp9itLZy20';
	private $_token = null;
	private $_token_expire_time = 60*60*24; // 1 DAY

	public function __construct()
	{
		$scrumsToken = variable_get('scrums_token');
		if(is_array($scrumsToken) && key_exists('access_token', $scrumsToken) && key_exists('expires_in', $scrumsToken) && $scrumsToken['expires_in'] > time()){
			$this->_token = $scrumsToken;
		}
		if (!$this->_token) {
			$this->getAuthToken();
		}
	}

	private function getAuthToken()
	{
		$url = $this->_url . 'oauth/token';

		$fields = array(
			'grant_type' => 'client_credentials',
			'client_id' => $this->_clientId,
			'client_secret' => $this->_clientSecret,
			'scope' => '',
		);

		$fields_string = '';
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
		var_dump($result);
		if ($result) {
			$this->_token = json_decode($result,true);
			$this->_token['expires_in'] = time() + $this->_token_expire_time;
			variable_set('scrums_token', $this->_token);
		} else {
			$this->_token = null;
		}
	}

	public function getData($url)
	{
		$targetUrl = $this->_url.'/web_client_v1/'. $url;
		$headers = [
			'Authorization: Bearer ' . $this->_token['access_token'],
			'Accept: application/json'
		];

		$ch = curl_init();
		$timeout = 5;
		curl_setopt($ch, CURLOPT_URL, $targetUrl);
		curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);

		$data = curl_exec($ch);
		curl_close($ch);
		return $data;
	}
}