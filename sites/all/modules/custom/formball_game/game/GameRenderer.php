<?php

require_once(drupal_get_path('module', 'formball_game') . '/game/renderElements/FormElement.php');

class GameRenderer {

  private $world;
  private $field;
  private $boxes;
  private $balls;

  public function __construct($game_world) {
    $this->world = $game_world;
    $this->init_game_objects();
  }

  public function render() {
    $form = array();
    $form['boxes'] = $this->render_boxes();
    $form['balls'] = $this->render_balls();
    return $form;
  }

  private function init_game_objects() {
    $this->field = $this->world->getField();
    $this->boxes = $this->field->getBoxes();
    $this->balls = $this->field->getBalls();
  }

  public function render_boxes() {
    $form_elements = array();

    foreach ($this->boxes as $key=>$box){
      $form_element = new FormElement();
      $form_element->id = $box->getName();
      $form_element->title = '';
      $checked = $box->has_player() == true ? 'checked' : '';
      $form_element->prefix = '<div class="' . $box->getName() .'" style="' .
        'position: absolute; ' .
        'top: ' . $box->pos_y . '%; ' .
        'left: '. $box->pos_x . '%;">';
      $form_element->value = $box->has_player();
      $form_element->attribute = $checked;
      $form_element->suffix = '<label for="' . $box->getName() . '"><span></span></label>' .
        '</div>';
      $form_element->is_opponent = $box->is_type() !== 'A';

      $form_elements[] = $form_element;
    }
    return $form_elements;
  }

  public function render_balls() {
    $form_elements = array();

    foreach ($this->balls as $key=>$ball){
      $form_element = new FormElement();

      $form_element->id = $ball->getName();
      $form_element->prefix = '<div class="' . $ball->getName() . '" style="' .
        'position: absolute; ' .
        'top: ' . $ball->pos_y . '%; ' .
        'left: '. $ball->pos_x . '%;">';
      $form_element->value = $ball->getName() === $ball->getPosition();
      $form_element->suffix = '<label for="' . $ball->getName() . '"></label>' . '</div>';

      $form_elements[] = $form_element;

    }

    return $form_elements;
  }

}