<?php

define('CCMP_NEWSLETTERS_API_URL', 'https://api.ccmp.eu');

/**
 * Class CCMP_Newsletters_API.
 *
 * Example use API:
 *
 * $api = new CCMP_Newsletters_API();
 * $contentblock = $api->createContentBlock($subject);
 * $compaign = $api->createEmailCampaign($filter_id, $subject, $body, $contentblock['result']);
 * $api->launchEmailCampaign($compaign['result']);
 * $api->deleteEmailCampaign($compaign['result']['campId']);
 * $api->deleteContentBlock($contentblock['result']['cont_id']);
 */
class CCMP_Newsletters_API {

  /**
   * Token for OAuth session.
   *
   * @var string
   */
  protected $token = '';

  /**
   * Get Oauth token.
   *
   * @param bool|FALSE $token
   *   (optional) Custom token for session if you have token.
   *
   * @throws \Exception
   */
  public function __construct($token = FALSE) {
    if (!$token) {
      $response = $this->getOauth2Token();

      if ($response['code'] == 200) {
        $this->token = $response['result']['access_token'];
      }
      else {
        throw new Exception('Access token was not received. Response: ' . print_r($response, TRUE));
      }
    }
    else {
      $this->token = $token;
    }
  }

  /**
   * Request to obtain a token.
   *
   * @return array
   * @throws \Exception
   */
  protected function getOauth2Token() {
    return $this->execute('POST', 'services/authorization/oauth2/token');
  }

  /**
   * Get token.
   *
   * @return bool|string
   */
  public function getToken() {
    return $this->token;
  }

  /**
   * Get info about compaign.
   *
   * @param int $camp_id
   *   Compaign ID.
   *
   * @return array
   * @throws \Exception
   */
  public function getEmailCampaign($camp_id) {
    return $this->execute('GET', 'services2/api/EmailCampaign?id=' . $camp_id);
  }

  /**
   * Create compaign.
   *
   * @param int $filter_id
   *   Filter ID.
   * @param string $subject
   *   Message subject.
   * @param string $body
   *   Message body.
   * @param array $contentblock
   *   Content block, see method CCMP_Newsletters_API::createContentBlock().
   *
   * @return array
   * @throws \Exception
   *
   * @see CCMP_Newsletters_API::createContentBlock()
   */
  public function createEmailCampaign($filter_id, $subject, $body, $contentblock, $body_text = '') {
    $body = $body . ' {[' . $contentblock['cont_name'] . '|' . $contentblock['cont_id'] . ']}';

    $data = array(
      "CustId" => variable_get('ccmp_newsletters_cust_id'),
      "EntityId" => "100",
      "TypeId" => "REGULAR",
      "ToFilterId" => $filter_id,
      "ContBodies" => array(
        array(
          "Type" => "HTML",
          "UsageMask" => "ALL_EMAIL_STYLE_USAGE_MASK",
          "Body" => $body,
        ),
        array(
          "type" => "TEXT",
          "usageMask" => "ALL_EMAIL_STYLE_USAGE_MASK",
          "body" => $body_text,
        ),
      ),
      "EmailMsgTemplate" => array(
        "FromName" => variable_get('ccmp_newsletters_from_name', ''),
        "ToName" => "{(email)}",
        "ToAddressPropId" => variable_get('ccmp_newsletters_to_address_prop_id'),
        "FromAddressId" => variable_get('ccmp_newsletters_from_address_id'),
        "Subject" => $subject,
      ),
      "Obj" => array(
        "display_name" => $subject,
      ),
      "CampAction" => 'APPROVE',
      "ApprovalRequired" => array(
        "Sending" => FALSE,
        "Personalization" => FALSE,
        "ContentCalculation" => FALSE,
      ),
      "campReviewFlags" => array(
        "contCalculationFlag" => FALSE,
        "personalizationFlag" => FALSE,
        "sendingFlag" => FALSE,
      ),
    );

    return $this->execute('POST', 'services2/api/EmailCampaign', $data);
  }

  /**
   * Launch compaign.
   *
   * @param array $data
   *   Compaign data from method "createEmailCampaign" or "getEmailCampaign".
   *
   * @return array
   * @throws \Exception
   *
   * @see CCMP_Newsletters_API::createEmailCampaign()
   * @see CCMP_Newsletters_API::getEmailCampaign()
   */
  public function launchEmailCampaign($data) {
    if (empty($data)) {
      return FALSE;
    }

    $data['CampAction'] = 'LAUNCH';

    return $this->execute('PUT', 'services2/api/EmailCampaign?id=' . $data['campId'], $data);
  }

  /**
   * Delete compaign.
   *
   * @param int $camp_id
   *   Compaign ID.
   *
   * @return array
   * @throws \Exception
   */
  public function deleteEmailCampaign($camp_id) {
    return $this->execute('DELETE', 'services2/api/EmailCampaign?id=' . $camp_id);
  }

  /**
   * Get info about contentblock.
   *
   * @param int $contentblock_id
   *   Contentblock ID.
   *
   * @return array
   * @throws \Exception
   */
  public function getContentBlock($contentblock_id) {
    return $this->execute('GET', 'services2/api/ContentBlock?Id=' . $contentblock_id);
  }

  /**
   * Create new content block.
   *
   * @param string $display_name
   *   Block name. Before create new content block, remove from name all special symbolic.
   *
   * @return array
   * @throws \Exception
   */
  public function createContentBlock($display_name) {
    $display_name = preg_replace('@[^a-z0-9-]+@', '-', strtolower($display_name));

    $data = array(
      'cust_id' => variable_get('ccmp_newsletters_cust_id'),
      'entity_id' => 100,
      'type_id' => 'PARAGRAPH',
      'ContBodies' => array(
        array(
          'type_id' => 'HTML',
          'usage_mask' => 'ALL_EMAIL_STYLE_USAGE_MASK',
        ),
      ),
      'ContModelProps' => array(),
      'ContParts' => array(),
      'Obj' => array(
        'display_name' => $display_name,
      ),
    );

    return $this->execute('POST', 'services2/api/ContentBlock', $data);
  }

  /**
   * Remove contentblock.
   *
   * @param int $cont_id
   *   Contentblock ID.
   *
   * @return array
   * @throws \Exception
   */
  public function deleteContentBlock($cont_id) {
    return $this->execute('DELETE', 'services2/api/ContentBlock?id=' . $cont_id);
  }

  /**
   * Request to API.
   *
   * @param string $method
   *   GET, POST, PUT, DELETE.
   * @param string $url
   *   Url to API method.
   * @param array $data
   *   (optional) POST, PUT data.
   *
   * @return array
   * @throws \Exception
   */
  public function execute($method, $url, $data = array()) {
    $clientId = variable_get('ccmp_newsletters_id_client', FALSE);
    $consumerKey = variable_get('ccmp_newsletters_key', FALSE);
    $consumerSecret = variable_get('ccmp_newsletters_password', FALSE);

    if (!$this->token) {
      $headers = array(
        'grant_type' => 'password',
        'client_id' => $clientId,
        'username' => $consumerKey,
        'password' => $consumerSecret,
        'content_type' => 'application/x-www-form-urlencoded',
      );
    }
    else {
      $headers = array(
        'Accept: application/json',
        'Content-Type: application/json',
        'Authorization: Bearer ' . $this->token,
      );
    }

    try {
      $curl = curl_init();
      curl_setopt($curl, CURLOPT_URL, CCMP_NEWSLETTERS_API_URL . '/' . $url);
      curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);

      switch (strtolower($method)) {
        case 'post':
          curl_setopt($curl, CURLOPT_POST, 'POST');

          if (!$this->token) {
            curl_setopt($curl, CURLOPT_POSTFIELDS, http_build_query($headers));
          }
          else {
            curl_setopt($curl, CURLOPT_POSTFIELDS, json_encode($data));
          }
          break;

        case 'put':
          curl_setopt($curl, CURLOPT_CUSTOMREQUEST, 'PUT');
          curl_setopt($curl, CURLOPT_POSTFIELDS, json_encode($data));
          break;

        case 'delete':
          curl_setopt($curl, CURLOPT_CUSTOMREQUEST, 'DELETE');
          break;

        case 'get':
          curl_setopt($curl, CURLOPT_CUSTOMREQUEST, 'GET');
          break;
      }

      curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
      $result = curl_exec($curl);
      $code = curl_getinfo($curl, CURLINFO_HTTP_CODE);

      curl_close($curl);

      return array_merge(array('code' => (int) $code), array('result' => json_decode($result, TRUE)));
    }
    catch (Exception $e) {
      throw new Exception("Error during the call. Here the message: " . $e->getMessage());
    }
  }

}
