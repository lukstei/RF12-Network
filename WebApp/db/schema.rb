# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended to check this file into your version control system.

ActiveRecord::Schema.define(:version => 20110203151352) do

  create_table "measured_datas", :force => true do |t|
    t.integer  "messdaten_int"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.integer  "sensor_id"
    t.datetime "messzeit"
  end

  create_table "sensor_types", :force => true do |t|
    t.string   "name"
    t.string   "unit"
    t.string   "formula"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.boolean  "is_analog"
  end

  create_table "sensors", :force => true do |t|
    t.datetime "created_at"
    t.datetime "updated_at"
    t.integer  "task_id"
    t.integer  "station_id"
    t.string   "name"
    t.integer  "sensor_type_id"
    t.integer  "analog_port"
    t.integer  "intervall"
    t.string   "intervall_unit"
  end

  create_table "stations", :force => true do |t|
    t.boolean  "active"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.string   "adress"
  end

  create_table "tasks", :force => true do |t|
    t.string   "title"
    t.text     "description"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

end
