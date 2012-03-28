class CreateClassbjs < ActiveRecord::Migration
  def change
    create_table :classbjs do |t|
      t.string :name
      t.references :department
      t.integer :score, :default => 0
      t.integer :num, :default => 0

      t.timestamps
    end
  end
end
