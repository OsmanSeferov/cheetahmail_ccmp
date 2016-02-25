<?php
/**
 * @file
 * Default theme implementation to display a newsletter subscribe popup.
 */
?>
<div id="wrapp">
  <a href="#" class="close">close</a>
  <h3><?php print t('S’abonner à <span>#La Lettre</span>'); ?></h3>
  <div class="form-newsletter">
    <div class="top">
      <a href="<?php print url('user/login'); ?>" class="btn-check"><?php print t('m’identifier'); ?></a>
      <h4><?php print t('J’ai déjà un compte Livres Hebdo'); ?>:</h4>
    </div>
    <h4><?php print t('Créer un compte Livres Hebdo'); ?>:</h4>
    <div class="frame">
      <div id="popup-newsletter-form">
        <?php print render($subscribe_form); ?>
      </div>
    </div>
    <div class="form-information">
      <p><?php print t('Electre respecte votre vie privée. Nous vous rappelons qu’en application de la loi n° 78-17 du 6 janvier 1978 relative à l’informatique, aux fichiers et aux libertés, vous disposez des droits d’opposition (article 26 de la loi), d’accès (articles 34 à 38 de la loi) et de rectification (article 36 de la loi) des données vous concernant.') ;?></p>
      <p><?php print t('Pour exercer ce droit, vous pouvez vous adresser à Livres Hebdo 35, rue Grègoire de Tours 75006 Paris'); ?></p>
    </div>
  </div>
</div>
